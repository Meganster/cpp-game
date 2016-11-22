//
// Created by artem on 13.11.16.
//

#include "TreeManager.h"


tree_management::TreeManager::TreeManager(): is_active(false) {
    addEvents();
};

void tree_management::TreeManager::createTreeManagers() {
    getFirstManager()->set_active();
    getSecondManager()->set_passive();
}

tree_management::TreeManager* tree_management::TreeManager::getActiveManager() {
    if (getFirstManager()->is_active && !getSecondManager()->is_active) {
        return getFirstManager();
    } else if (getSecondManager()->is_active && !getFirstManager()->is_active) {
        return getSecondManager();
    } else {
        return nullptr;
    }
}

tree_management::TreeManager* tree_management::TreeManager::getPassiveManager() {
    if (getFirstManager()->is_active && !getSecondManager()->is_active) {
        return getSecondManager();
    } else if (getSecondManager()->is_active && !getFirstManager()->is_active) {
        return getFirstManager();
    } else {
        return nullptr;
    }
}

void tree_management::TreeManager::switchManagers() {
    getFirstManager()->switchState();
    getSecondManager()->switchState();
}

tree_management::TreeManager* tree_management::TreeManager::getFirstManager() {
    static TreeManager first_tree_manager = TreeManager();

    return &first_tree_manager;
}

tree_management::TreeManager* tree_management::TreeManager::getSecondManager() {
    static TreeManager second_tree_manager = TreeManager();

    return &second_tree_manager;
}

void tree_management::TreeManager::set_active() {
    is_active = true;
}

void tree_management::TreeManager::set_passive() {
    is_active = false;
}

void tree_management::TreeManager::switchState() {
    is_active = !is_active;
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

/*
TreeManagement::TreeManagement() {};

TreeManagement::~TreeManagement() {};

void TreeManagement::addEvents() {
    //auto call_back = [](TreeNodeSelectedEvent* event) -> void {
    //    std::cout << event->someVar << std::endl;
    //};

    //auto listener = event_wrappers::create_listener<TreeNodeSelectedEvent>(call_back);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void TreeManagement::initOptions() {};

TreeManagement* TreeManagement::create() {
    TreeManagement* tree_manager_ptr = new TreeManagement();

    if (tree_manager_ptr->initWithFile(TreeNode::kSpritePath)) {
        tree_manager_ptr->autorelease();
        tree_manager_ptr->initOptions();
        tree_manager_ptr->addEvents();

        return tree_manager_ptr;
    }

    CC_SAFE_DELETE(tree_manager_ptr);
    return NULL;

}
*/