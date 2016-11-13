//
// Created by artem on 13.11.16.
//

#include "TreeManager.h"
#include "event_wrappers.h"
#include <iostream>

TreeManager::TreeManager() {};

TreeManager::~TreeManager() {};

void TreeManager::addEvents() {
    auto call_back = [](TreeNodeSelectedEvent* event) -> void {
        std::cout << event->someVar << std::endl;
    };

    auto listener = EventWrapper::create_listener<TreeNodeSelectedEvent>(call_back);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void TreeManager::initOptions() {};

TreeManager* TreeManager::create() {
    TreeManager* tree_manager_ptr = new TreeManager();

    if (tree_manager_ptr->initWithFile(TreeNode::kSpritePath)) {
        tree_manager_ptr->autorelease();
        tree_manager_ptr->initOptions();
        tree_manager_ptr->addEvents();

        return tree_manager_ptr;
    }

    CC_SAFE_DELETE(tree_manager_ptr);
    return NULL;

}