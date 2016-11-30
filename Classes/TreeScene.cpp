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

    auto start_point = Vec2(origin.x + 20, visibleSize.height/2 + origin.y);

    for (int i = 0; i != 10; ++i) {
        auto node_ptr =TreeNode::create();
        if (node_ptr != NULL) {
            node_ptr->setPosition(start_point.x +80 * i, start_point.y + 20);
            this->addChild(node_ptr, 10);
        }
    }


    auto button = ui::Button::create("button_cancel.png");
    button->setPosition(Point(visibleSize.width - 50, visibleSize.height - 50));
    button->setSwallowTouches(true);
    button->addClickEventListener([this](Ref* pSender) -> void { tree_events::RevertLastChangeEvent(); std::cout<<"Cancel" << std::endl;});
    this->addChild(button, 12);

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

    auto listenerAdd = event_wrappers::create_listener<tree_events::TreeNodeCreationEvent>\
([](tree_events::TreeNodeCreationEvent* event) -> void { std::cout << "Nodes creation!" << std::endl;});
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerAdd, this);


    auto mouse_listener = cocos2d::EventListenerMouse::create();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouse_listener, this);
    mouse_listener->onMouseDown = [this] (cocos2d::EventMouse* event) {
        if (event->getMouseButton() == MOUSE_BUTTON_LEFT) {
            this->addNode(event, this);
        };
    };
}
