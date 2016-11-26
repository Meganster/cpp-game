//
// Created by artem on 21.10.16.
//

#include "TreeScene.h"
#include "TreeNode.h"
#include <iostream>
#include "event_system/EventWrappers.h"
#include "managers/TreeManagement/TreeManager.h"
USING_NS_CC;

Scene* TreeScene::createScene() {
    return TreeScene::create();
}

bool TreeScene::init() {
    if (!Scene::init()) {
        return false;
    }

    addEvents();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    auto start_point = Vec2(origin.x + 20, visibleSize.height/2 + origin.y);

    std::vector<TreeNode*> node_ptr_vec;
    for (int i = 0; i != 10; ++i) {
        auto node_ptr =TreeNode::create();
        if (node_ptr != NULL) {
            node_ptr->setPosition(start_point.x + 40 * i, start_point.y);
            this->addChild(node_ptr, 10);
            node_ptr_vec.push_back(node_ptr);
        }
    }

    return true;
}

/*void TreeScene::addNode(cocos2d::EventMouse* event, cocos2d::Scene* scene_ptr) {
    cocos2d::Vec2 event_point = event->getLocation();
    auto e = tree_events::TreeNodeCreationEvent(event_point, scene_ptr);
    //scene_ptr->_eventDispatcher->dispatchEvent(&e);
}*/


void TreeScene::addEvents() {
    /*auto mouse_listener = cocos2d::EventListenerMouse::create();

    mouse_listener->onMouseUp = [this] (cocos2d::EventMouse* event) {
        if (event->getMouseButton() == MOUSE_BUTTON_LEFT) {
            this->addNode(event, this);
        }
    };*/

    auto listenerSelect = event_wrappers::create_listener<tree_events::TreeNodeSelectionEvent>\
([](tree_events::TreeNodeSelectionEvent* event) -> void {event->selected_node->setScale(0.12);});
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerSelect, this);

    auto listenerDeselect = event_wrappers::create_listener<tree_events::TreeNodeDeselectionEvent>\
([](tree_events::TreeNodeDeselectionEvent* event) -> void {event->deselected_node->setScale(0.1);});
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerDeselect, this);

    auto listenerAdd = event_wrappers::create_listener<tree_events::TreeNodeCreationEvent>\
([](tree_events::TreeNodeCreationEvent* event) -> void { std::cout << "Nodes creation!" << std::endl;});
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerAdd, this);
}

void TreeScene::treeNodeSelectedCallback(TreeNodeSelectedEvent* event, TreeScene* tree_scene) {
    TreeNode* tree_node_ptr = (TreeNode*)event->getUserData();
    tree_node_ptr->setScale(0.25);
}
