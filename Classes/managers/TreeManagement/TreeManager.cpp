//
// Created by artem on 13.11.16.
//

#include "TreeManager.h"
#include "../ScoreManagement/ScoreManagement.h"
#include <iostream>
#include <vector>

using namespace tree_management;

void TreeChange::submit() {}

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


TreeManager::TreeManager(): is_active{false}{
    selected_nodes = std::set<tree_interfaces::TreeNodeInterface*>();
    addEvents();
};

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

void TreeManager::selectNode(tree_interfaces::TreeNodeInterface* node) {
    selected_nodes.insert(node);
}

void TreeManager::deselectNode(tree_interfaces::TreeNodeInterface* node) {
    if (selected_nodes.count(node)) {
        selected_nodes.erase(node);
    }
}

void TreeManager::addEvents() {
    auto node_selected_call_back = [this](tree_events::TreeNodeSelectionEvent* event) -> void {
        manageTreeNodeSelectionEvent(event);
    };
    auto node_selected_listener = event_wrappers::create_listener<tree_events::TreeNodeSelectionEvent>(node_selected_call_back);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(node_selected_listener, 1);


    auto node_deselected_call_back = [this](tree_events::TreeNodeDeselectionEvent* event) -> void {
        manageTreeNodeDeselectionEvent(event);
    };
    auto node_deselected_listener = event_wrappers::create_listener<tree_events::TreeNodeDeselectionEvent>(node_deselected_call_back);
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(node_deselected_listener, 1);


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
}

void TreeManager::manageTreeNodeSelectionEvent(tree_events::TreeNodeSelectionEvent* event) {
    selectNode(event->selected_node);
    std::cout << "Tree manager: node selected" << std::endl;
    std::cout << "Total selected " << selected_nodes.size() << std::endl << std::endl;
}

void TreeManager::manageTreeNodeDeselectionEvent(tree_events::TreeNodeDeselectionEvent* event) {
    deselectNode(event->deselected_node);

    std::cout << "Tree manager: node deselected" << std::endl;
    std::cout << "Total selected " << selected_nodes.size() << std::endl << std::endl;
}

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
        tree_changes.push(tree_change);

        edge_factory->closeRequest();

        std::cout << "Tree manager: edge created" << std::endl;
    } else {
        std::cout << "Not enough money." << " Have: " << score_manager.getActivePlayerScore() << " Need: " << edge_factory->getBuyPrice() << std::endl;
    }
}

void TreeManager::manageTreeEdgeDeletionEvent(tree_events::TreeEdgeDeletionEvent* event) {
    auto score_manager = score_management::ScoreManager::getInstance();

    auto edge = event->edge_to_delete;
    score_manager.sell(edge);

    edge->removeFromParentAndCleanup(true);
}

void TreeManager::manageTreeNodeCreationEvent(tree_events::TreeNodeCreationEvent* event) {
    auto edge_factory = event->edge_factory;
    auto score_manager = score_management::ScoreManager::getInstance();
    auto scene = event->scene;

    TreeNodeInterface* new_node = event->new_node;
    edge_factory->setRequest(new_node, selected_nodes);

    if (selected_nodes.size() == 0) {
        return;
    }

    if (score_manager.hasEnoughMoney(edge_factory)) {
        auto tree_change = TreeChange();
        tree_change.addTreePart(new_node);

        scene->addChild(new_node);

        auto edges = edge_factory->getEdges();

        auto edge_iter = edges.begin();
        auto node_iter = selected_nodes.begin();
        for (; edge_iter != edges.end() && node_iter != selected_nodes.end(); ++edge_iter, ++node_iter) {
            auto edge = *edge_iter;
            auto start_node = *node_iter;
            start_node->setDeselected();

            edge->setNodes(start_node, new_node);

            tree_change.addTreePart(edge);
            scene->addChild(edge);
        }

        edge_factory->closeRequest();
        tree_changes.push(tree_change);
        selected_nodes.clear();

        std::cout << "Tree manager: edge created" << std::endl;
    } else {
        std::cout << "Not enough money." << " Have: " << score_manager.getActivePlayerScore() << " Need: " << edge_factory->getBuyPrice() << std::endl;
    }


}

void TreeManager::manageRevertChangeEvent(tree_events::RevertLastChangeEvent* event) {
    revertLastChange();
}


TreeManagerHolder::TreeManagerHolder(std::shared_ptr<TreeManager> manager_1_, std::shared_ptr<TreeManager> manager_2_):
        manager_1{manager_1_}, manager_2{manager_2_} {
    if ((manager_1->isActive() && manager_2->isActive()) || (!manager_1->isActive() && !manager_2->isActive())) {
        manager_1->setActive();
        manager_2->setPassive();
    }
};

std::shared_ptr<TreeManager> TreeManagerHolder::getActiveManager() {
    if (manager_1->isActive() && !manager_2->isActive()) {
        return manager_1;
    } else if (manager_2->isActive() && !manager_2->isActive()) {
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

void TreeManagerHolder::switchManagers() {
    manager_1->switchState();
    manager_2->switchState();
}

std::shared_ptr<TreeManager> TreeManagerHolder::getFirstManager() {
    return manager_1;
}

std::shared_ptr<TreeManager> TreeManagerHolder::getSecondManager() {
    return manager_2;
}