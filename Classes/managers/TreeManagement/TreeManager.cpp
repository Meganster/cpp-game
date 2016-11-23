//
// Created by artem on 13.11.16.
//

#include "TreeManager.h"
#include "../ScoreManagement/ScoreManagement.h"


tree_management::TreeManager::TreeManager(): is_active{false}, edge_factory{nullptr} {
    addEvents();
};

tree_management::TreeManager::TreeManager(bool is_active, std::shared_ptr<tree_interfaces::EdgeFactoryInterface> edge_factory):
        is_active{is_active}, edge_factory{edge_factory} {};

void tree_management::TreeManager::switchState() {
    is_active = !is_active;
}

void tree_management::TreeManager::setFactory(std::shared_ptr<tree_interfaces::EdgeFactoryInterface> factory) {
    edge_factory = factory;
}

void tree_management::TreeManager::setActive() {
    is_active = true;
}

void tree_management::TreeManager::setPassive() {
    is_active = false;
}

bool tree_management::TreeManager::isActive() {
    return is_active;
}

void tree_management::TreeManager::selectNode(tree_interfaces::TreeNodeInterface* node) {
    selected_nodes.insert(node);
}

void tree_management::TreeManager::deselectNode(tree_interfaces::TreeNodeInterface* node) {
    if (selected_nodes.count(node)) {
        selected_nodes.erase(node);
    }
}

void tree_management::TreeManager::addEvents() {
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

void tree_management::TreeManager::manageTreeNodeSelectionEvent(tree_events::TreeNodeSelectionEvent* event) {
    selectNode(event->selected_node);
}

void tree_management::TreeManager::manageTreeNodeDeselectionEvent(tree_events::TreeNodeDeselectionEvent* event) {
    deselectNode(event->deselected_node);
}

void tree_management::TreeManager::manageTreeEdgeCreationEvent(tree_events::TreeEdgeCreationEvent* event) {
    cocos2d::Vec2 point_1 = event->tree_node_1->getPosition();
    cocos2d::Vec2 point_2 = event->tree_node_2->getPosition();

    edge_factory->setRequest(point_1, point_2);

    auto score_manager = score_management::ScoreManager::getInstance();

    if (score_manager.requestObjectCreation(edge_factory)) {

    }
    //TODO Add implementation
}

void tree_management::TreeManager::manageTreeEdgeDeletionEvent(tree_events::TreeEdgeDeletionEvent* event) {
    //TODO Add implementation
}

void tree_management::TreeManager::manageTreeNodeCreationEvent(tree_events::TreeNodeCreationEvent* event) {
    //TODO Add implementation
}


tree_management::TreeManagerHolder::TreeManagerHolder(std::shared_ptr<tree_management::TreeManager> manager_1_,
                                                      std::shared_ptr<tree_management::TreeManager> manager_2_):
        manager_1{manager_1_}, manager_2{manager_2_} {
    if ((manager_1->isActive() && manager_2->isActive()) || (!manager_1->isActive() && !manager_2->isActive())) {
        manager_1->setActive();
        manager_2->setPassive();
    }
};

std::shared_ptr<tree_management::TreeManager> tree_management::TreeManagerHolder::getActiveManager() {
    if (manager_1->isActive() && !manager_2->isActive()) {
        return manager_1;
    } else if (manager_2->isActive() && !manager_2->isActive()) {
        return manager_2;
    } else {
        return nullptr;
    }
}

std::shared_ptr<tree_management::TreeManager> tree_management::TreeManagerHolder::getPassiveManager() {
    if (manager_1->isActive() && !manager_2->isActive()) {
        return manager_2;
    } else if (manager_2->isActive() && !manager_2->isActive()) {
        return manager_1;
    } else {
        return nullptr;
    }
}

void tree_management::TreeManagerHolder::switchManagers() {
    manager_1->switchState();
    manager_2->switchState();
}

std::shared_ptr<tree_management::TreeManager> tree_management::TreeManagerHolder::getFirstManager() {
    return manager_1;
}

std::shared_ptr<tree_management::TreeManager> tree_management::TreeManagerHolder::getSecondManager() {
    return manager_2;
}