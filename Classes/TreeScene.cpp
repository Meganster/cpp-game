//
// Created by artem on 21.10.16.
//

#include "TreeScene.h"
#include "TreeParts/EdgeFunctionality/EdgeFactory.h"
#include <iostream>
#include "ui/CocosGUI.h"
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

    auto start_point = Vec2(visibleSize.width / 2, visibleSize.height/2);


    int start_length = 50;

    auto left_bottom_1 = TreeNode::create();
    left_bottom_1->setPosition(start_point.x - start_length - 300, start_point.y - start_length);
    this->addChild(left_bottom_1, left_bottom_1->getScenePriority());

    auto right_bottom_1 = TreeNode::create();
    right_bottom_1->setPosition(start_point.x + start_length - 300, start_point.y - start_length);
    this->addChild(right_bottom_1, left_bottom_1->getScenePriority());

    auto right_top_1 = TreeNode::create();
    right_top_1->setPosition(start_point.x + start_length - 300, start_point.y + start_length);
    this->addChild(right_top_1, left_bottom_1->getScenePriority());

    auto left_top_1 = TreeNode::create();
    left_top_1->setPosition(start_point.x - start_length - 300, start_point.y + start_length);
    this->addChild(left_top_1, left_bottom_1->getScenePriority());


    auto edge_1_1 = TreeEdge::create(left_bottom_1, right_bottom_1);
    this->addChild(edge_1_1, 5);

    auto edge_2_1 = TreeEdge::create(right_bottom_1, right_top_1);
    this->addChild(edge_2_1, 5);

    auto edge_3_1 = TreeEdge::create(right_top_1, left_top_1);
    this->addChild(edge_3_1, 5);

    auto edge_4_1 = TreeEdge::create(left_top_1, left_bottom_1);
    this->addChild(edge_4_1, 5);

    auto edge_5_1 = TreeEdge::create(left_bottom_1, right_top_1);
    this->addChild(edge_5_1, 5);

    auto edge_6_1 = TreeEdge::create(right_bottom_1, left_top_1);
    this->addChild(edge_6_1, 5);


    auto left_bottom_2 = TreeNode::create();
    left_bottom_2->setPosition(start_point.x - start_length + 300, start_point.y - start_length);
    this->addChild(left_bottom_2, left_bottom_2->getScenePriority());

    auto right_bottom_2 = TreeNode::create();
    right_bottom_2->setPosition(start_point.x + start_length + 300, start_point.y - start_length);
    this->addChild(right_bottom_2, left_bottom_2->getScenePriority());

    auto right_top_2 = TreeNode::create();
    right_top_2->setPosition(start_point.x + start_length + 300, start_point.y + start_length);
    this->addChild(right_top_2, left_bottom_2->getScenePriority());

    auto left_top_2 = TreeNode::create();
    left_top_2->setPosition(start_point.x - start_length + 300, start_point.y + start_length);
    this->addChild(left_top_2, left_bottom_2->getScenePriority());


    auto edge_1_2 = TreeEdge::create(left_bottom_2, right_bottom_2);
    this->addChild(edge_1_2, 5);

    auto edge_2_2 = TreeEdge::create(right_bottom_2, right_top_2);
    this->addChild(edge_2_2, 5);

    auto edge_3_2 = TreeEdge::create(right_top_2, left_top_2);
    this->addChild(edge_3_2, 5);

    auto edge_4_2 = TreeEdge::create(left_top_2, left_bottom_2);
    this->addChild(edge_4_2, 5);

    auto edge_5_2 = TreeEdge::create(left_bottom_2, right_top_2);
    this->addChild(edge_5_2, 5);

    auto edge_6_2 = TreeEdge::create(right_bottom_2, left_top_2);
    this->addChild(edge_6_2, 5);


    auto button_revert = ui::Button::create("Undo.png");
    button_revert->setPosition(Point(visibleSize.width - 100, visibleSize.height - 100));
    button_revert->setSwallowTouches(true);
    button_revert->addClickEventListener([this](Ref* pSender) -> void {
        auto event = tree_events::RevertLastChangeEvent();
        this->_eventDispatcher->dispatchEvent(&event); });
    this->addChild(button_revert, 12);


    auto button_submit = ui::Button::create("button_cancel.png");
    button_submit->setPosition(Point(visibleSize.width - 50, visibleSize.height - 500));
    button_submit->setSwallowTouches(true);
    button_submit->addClickEventListener([this](Ref* pSender) -> void {
        auto event = tree_events::SubmitChangesEvent();
        this->_eventDispatcher->dispatchEvent(&event); });
    this->addChild(button_submit, 12);

    return true;
}

void TreeScene::addNode(cocos2d::EventMouse* event, cocos2d::Scene* scene_ptr) {
    auto new_node = TreeNode::create();
    new_node->setPosition(event->getLocationInView());

    auto factory = EdgeFactory::getInstance();
    factory.setPrototype(TreeEdge::create());

    auto e = tree_events::TreeNodeCreationEvent(new_node, scene_ptr, &factory);

    Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
}


void TreeScene::addEvents() {

    auto mouse_listener = cocos2d::EventListenerMouse::create();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouse_listener, this);
    mouse_listener->onMouseDown = [this] (cocos2d::EventMouse* event) {
        if (event->getMouseButton() == MOUSE_BUTTON_LEFT) {
            this->addNode(event, this);
        };
    };
}
