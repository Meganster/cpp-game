//
// Created by artem on 21.10.16.
//

#include "TreeScene.h"
#include "TreeNode.h"
#include <iostream>
#include "event_system/event_wrappers.h"
#include "managers/TreeManager.h"
USING_NS_CC;

Scene* TreeScene::createScene() {
    auto scene = cocos2d::Scene::create();
    auto layer = TreeScene::create();
    scene->addChild(layer);

    return scene;
}

bool TreeScene::init() {
    if (!Layer::init()) {
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

    auto tree_manager = TreeManager::create();
    this->addChild(tree_manager, 100);

    return true;
}

void TreeScene::addEvents() {
}

void TreeScene::treeNodeSelectedCallback(TreeNodeSelectedEvent* event, TreeScene* tree_scene) {
    TreeNode* tree_node_ptr = (TreeNode*)event->getUserData();
    tree_node_ptr->setScale(0.25);
}
