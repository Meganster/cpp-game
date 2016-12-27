//
// Created by artem on 13.11.16.
//

#include "TreeManager.h"
#include "../ScoreManagement/ScoreManagement.h"
#include <iostream>

using namespace tree_management;

void TreeChange::submit() {
    for (auto tree_part: tree_parts) {
        tree_part->submit();
    }
}

void TreeChange::revert() {
    auto score_manager = score_management::ScoreManager::getInstance();

    for (auto tree_part: tree_parts) {
        score_manager.revert(tree_part);
        tree_part->removeFromParentAndCleanup(true);
    }
}

void TreeChange::addTreePart(tree_interfaces::TreePart * tree_part) {
    tree_parts.push_back(tree_part);
}


TreeManager::TreeManager(cocos2d::Rect control_area) {
    is_active = false;
}

void TreeManager::switchState() {
    is_active = !is_active;
}

void TreeManager::setActive() {
    is_active = true;
}

void TreeManager::setPassive() {
    is_active = false;
}

bool TreeManager::isActive() {
    return is_active;
}

bool TreeManager::revertLastChange() {
    if (!tree_changes.empty()) {
        TreeChange last_change = tree_changes.top();
        last_change.revert();
        tree_changes.pop();
        return true;
    }
    return false;
}

void TreeManager::submitChanges() {
    while (!tree_changes.empty()) {
        auto change = tree_changes.top();
        change.submit();
        tree_changes.pop();
    }
}

void TreeManager::addChange(TreeChange tree_change) {
    tree_changes.push(tree_change);
}

void TreeManager::addEvents() {}

void TreeManager::manageTreeEdgeCreationEvent(tree_events::TreeEdgeCreationEvent* event) {
    auto edge_factory = event->edge_factory;
    auto scene = event->scene;

    edge_factory->setRequest(event->tree_node_1, event->tree_node_2);

    auto score_manager = score_management::ScoreManager::getInstance();

    if (score_manager.hasEnoughMoney(edge_factory)) {
        auto edge = edge_factory->getEdges()[0];

        score_manager.buy(edge);
        scene->addChild(edge);

        auto tree_change = TreeChange();
        tree_change.addTreePart(edge);
        addChange(tree_change);

        edge_factory->closeRequest();

        std::cout << "Tree manager: edge created" << std::endl;
    } else {
        std::cout << "Not enough money." << " Have: " << score_manager.getActivePlayerScore() << " Need: " << edge_factory->getBuyPrice() << std::endl;
    }
}

void TreeManager::manageTreeEdgeDeletionEvent(tree_events::TreeEdgeDeletionEvent* event) {
    auto score_manager = score_management::ScoreManager::getInstance();

    auto edge = event->tree_edge_;
    score_manager.sell(edge);

    edge->destroy();
}

void TreeManager::manageTreeNodeCreationEvent(tree_events::TreeNodeCreationEvent* event) {
    auto edge_factory = event->edge_factory;
    auto score_manager = score_management::ScoreManager::getInstance();
    auto scene = event->scene;

    TreeNodeInterface* new_node = event->new_node;
    edge_factory->setRequest(new_node, event->selected_nodes);

    for (auto node: event->selected_nodes) {
        node->setDeselected();
    }

    if (event->selected_nodes.size() < 2) {
        return;
    }

    if (score_manager.hasEnoughMoney(edge_factory)) {
        auto tree_change = TreeChange();
        tree_change.addTreePart(new_node);

        scene->addChild(new_node, new_node->getScenePriority());

        auto edges = edge_factory->getEdges();

        auto edge_iter = edges.begin();
        auto node_iter = event->selected_nodes.begin();
        for (; edge_iter != edges.end() && node_iter != event->selected_nodes.end(); ++edge_iter, ++node_iter) {
            auto edge = *edge_iter;
            auto start_node = *node_iter;

            edge->setNodes(start_node, new_node);

            tree_change.addTreePart(edge);
            scene->addChild(edge, edge->getScenePriority());
            scene->getPhysicsWorld()->addJoint(edge->getSpring());
        }

        edge_factory->closeRequest();
        tree_changes.push(tree_change);
        event->selected_nodes.clear();

        std::cout << "Tree manager: node created" << std::endl;
    } else {
        std::cout << "Not enough money." << " Have: " << score_manager.getActivePlayerScore() << " Need: " << edge_factory->getBuyPrice() << std::endl;
    }


}

void TreeManager::manageForceApplyingEvent(tree_events::ForceApplyingEvent *event) {
    auto score_manager = score_management::ScoreManager::getInstance();
    auto scene = event->node->getScene();
    auto force = event->force;

    if (score_manager.hasEnoughMoney(force)) {
        auto tree_change = TreeChange();
        tree_change.addTreePart(force);

        scene->addChild(force, force->getScenePriority());
        tree_changes.push(tree_change);

        std::cout << "Tree manager: force created" << std::endl;
    } else {
        std::cout << "Not enough money." << " Have: " << score_manager.getActivePlayerScore() << " Need: " << force->getBuyPrice() << std::endl;
    }
}

void TreeManager::manageRevertChangeEvent(tree_events::RevertLastChangeEvent*) {
    std::cout << "Change revert" << std::endl;
    revertLastChange();
}

void TreeManager::manageSubmitChangesEvent(tree_events::SubmitChangesEvent *) {
    std::cout << "Change submit" << std::endl;
    submitChanges();
}


TreeManagerHolder::TreeManagerHolder(cocos2d::Scene *scene) {
    auto visible_size = cocos2d::Director::getInstance()->getVisibleSize();
    auto left_rect = cocos2d::Rect(0, 0, visible_size.width / 2, visible_size.height);
    auto right_rect = cocos2d::Rect(visible_size.width / 2, 0, visible_size.width / 2, visible_size.height);

    manager_1 = std::shared_ptr<TreeManager>(new TreeManager(left_rect));
    manager_1->setActive();
    control_zone_1 = ControlZone::create(left_rect);
    scene->addChild(control_zone_1, control_zone_1->getScenePriority());
    control_zone_1->setActive();

    manager_2 = std::shared_ptr<TreeManager>(new TreeManager(right_rect));
    manager_2->setPassive();
    control_zone_2 = ControlZone::create(right_rect);
    scene->addChild(control_zone_2, control_zone_2->getScenePriority());
    control_zone_2->setPassive();

    addEvents();
}

std::shared_ptr<TreeManager> TreeManagerHolder::getActiveManager() {
    if (manager_1->isActive() && !manager_2->isActive()) {
        return manager_1;
    } else if (manager_2->isActive() && !manager_1->isActive()) {
        return manager_2;
    } else {
        return nullptr;
    }
}

std::shared_ptr<TreeManager> TreeManagerHolder::getPassiveManager() {
    if (manager_1->isActive() && !manager_2->isActive()) {
        return manager_2;
    } else if (manager_2->isActive() && !manager_2->isActive()) {
        return manager_1;
    } else {
        return nullptr;
    }
}

void TreeManagerHolder::makeTurn() {
    manager_1->switchState();
    manager_2->switchState();

    control_zone_1->switchState();
    control_zone_2->switchState();
}

std::shared_ptr<TreeManager> TreeManagerHolder::getFirstManager() {
    return manager_1;
}

std::shared_ptr<TreeManager> TreeManagerHolder::getSecondManager() {
    return manager_2;
}

void TreeManagerHolder::manageTreeNodeCreationEvent(tree_events::TreeNodeCreationEvent *event)  {
    auto active_manager = getActiveManager();
    active_manager->manageTreeNodeCreationEvent(event);
}

void TreeManagerHolder::manageForceApplyingEvent(tree_events::ForceApplyingEvent *event) {
    auto active_manager = getActiveManager();
    active_manager->manageForceApplyingEvent(event);

};

void TreeManagerHolder::manageTreeEdgeCreationEvent(tree_events::TreeEdgeCreationEvent *event)  {
    auto active_manager = getActiveManager();
    active_manager->manageTreeEdgeCreationEvent(event);
}

void TreeManagerHolder::manageTreeEdgeDeletionEvent(tree_events::TreeEdgeDeletionEvent *event)  {
    getActiveManager()->manageTreeEdgeDeletionEvent(event);
}

void TreeManagerHolder::manageRevertChangeEvent(tree_events::RevertLastChangeEvent *event) {
    getActiveManager()->manageRevertChangeEvent(event);
}

void TreeManagerHolder::manageSubmitChangesEvent(tree_events::SubmitChangesEvent *event) {
    getActiveManager()->manageSubmitChangesEvent(event);
    makeTurn();
}

void TreeManagerHolder::addEvents() {
    auto revert_change_call_back = [this](tree_events::RevertLastChangeEvent* event) -> void  {
        manageRevertChangeEvent(event);
    };
    auto revert_change_listener = event_wrappers::create_listener<tree_events::RevertLastChangeEvent>(revert_change_call_back);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(revert_change_listener, 1);

    auto submit_call_back = [this](tree_events::SubmitChangesEvent* event) -> void {
        manageSubmitChangesEvent(event);
    };
    auto submit_changes_listener = event_wrappers::create_listener<tree_events::SubmitChangesEvent>(submit_call_back);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(submit_changes_listener, 1);

    auto node_created_call_back = [this](tree_events::TreeNodeCreationEvent* event) -> void {
        manageTreeNodeCreationEvent(event);
    };
    auto node_created_listener = event_wrappers::create_listener<tree_events::TreeNodeCreationEvent>(node_created_call_back);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(node_created_listener, 1);


    auto edge_created_call_back = [this](tree_events::TreeEdgeCreationEvent* event) -> void {
        manageTreeEdgeCreationEvent(event);
    };
    auto edge_created_listener = event_wrappers::create_listener<tree_events::TreeEdgeCreationEvent>(edge_created_call_back);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(edge_created_listener, 1);


    auto edge_deleted_call_back = [this](tree_events::TreeEdgeDeletionEvent* event) -> void {
        manageTreeEdgeDeletionEvent(event);
    };
    auto edge_deleted_listener = event_wrappers::create_listener<tree_events::TreeEdgeDeletionEvent>(edge_deleted_call_back);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(edge_deleted_listener, 1);


    auto force_added_call_back = [this](tree_events::ForceApplyingEvent* event) -> void {
        manageForceApplyingEvent(event);
    };
    auto force_added_listener = event_wrappers::create_listener<tree_events::ForceApplyingEvent>(force_added_call_back);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(force_added_listener, 1);
}