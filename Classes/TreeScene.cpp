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


    auto left_bottom = TreeNode::create();
    left_bottom->setPosition(start_point.x - 100, start_point.y - 100);
    this->addChild(left_bottom, left_bottom->getScenePriority());

    auto right_bottom = TreeNode::create();
    right_bottom->setPosition(start_point.x + 100, start_point.y - 100);
    this->addChild(right_bottom, left_bottom->getScenePriority());

    auto right_top = TreeNode::create();
    right_top->setPosition(start_point.x + 100, start_point.y + 100);
    this->addChild(right_top, left_bottom->getScenePriority());

    auto left_top = TreeNode::create();
    left_top->setPosition(start_point.x - 100, start_point.y + 100);
    this->addChild(left_top, left_bottom->getScenePriority());


    auto edge_1 = TreeEdge::create(left_bottom, right_bottom);
    this->addChild(edge_1, 5);

    auto edge_2 = TreeEdge::create(right_bottom, right_top);
    this->addChild(edge_2, 5);

    auto edge_3 = TreeEdge::create(right_top, left_top);
    this->addChild(edge_3, 5);

    auto edge_4 = TreeEdge::create(left_top, left_bottom);
    this->addChild(edge_4, 5);

    auto edge_5 = TreeEdge::create(left_bottom, right_top);
    this->addChild(edge_5, 5);

    auto edge_6 = TreeEdge::create(right_bottom, left_top);
    this->addChild(edge_6, 5);


    auto button_revert = ui::Button::create("button_cancel.png");
    button_revert->setPosition(Point(visibleSize.width - 50, visibleSize.height - 50));
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

    auto listenerSelect = event_wrappers::create_listener<tree_events::TreeNodeSelectionEvent>\
([](tree_events::TreeNodeSelectionEvent* event) -> void {event->selected_node->setScale(0.12);});
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerSelect, this);

    auto listenerDeselect = event_wrappers::create_listener<tree_events::TreeNodeDeselectionEvent>\
([](tree_events::TreeNodeDeselectionEvent* event) -> void {event->deselected_node->setScale(0.1);});
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerDeselect, this);

    //auto listenerAdd = event_wrappers::create_listener<tree_events::TreeNodeCreationEvent>\
//([](tree_events::TreeNodeCreationEvent* event) -> void { std::cout << "Nodes creation!" << std::endl;});
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerAdd, this);


    auto mouse_listener = cocos2d::EventListenerMouse::create();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouse_listener, this);
    mouse_listener->onMouseDown = [this] (cocos2d::EventMouse* event) {
        if (event->getMouseButton() == MOUSE_BUTTON_LEFT) {
            this->addNode(event, this);
        };
    };
}
