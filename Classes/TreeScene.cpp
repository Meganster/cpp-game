//
// Created by artem on 21.10.16.
//

#include "TreeScene.h"
#include "TreeParts/EdgeFunctionality/EdgeFactory.h"
#include "./managers/ScoreManagement/ScoreManagement.h"
USING_NS_CC;

Scene* TreeScene::createScene() {
    auto scene = new TreeScene();
    if (scene && scene->initWithPhysics()) {
        scene->autorelease();
    } else {
        CC_SAFE_DELETE(scene);
        return nullptr;
    }
    scene->init();
    scene->addEvents();

    return scene;
}

bool TreeScene::init() {
    if (!Scene::init()) {
        return false;
    }

    addEvents();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    score_management::ScoreManager& score_manager = score_management::ScoreManager::getInstance();
    score_manager.setPlayer1Score(1000);
    score_manager.setPlayer2Score(1000);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    auto start_point = Vec2(visibleSize.width / 2, visibleSize.height/2);

    int start_length = 50;

    createStartStructure(cocos2d::Vec2(start_point.x - 300, start_point.y - 200), start_length);
    createStartStructure(cocos2d::Vec2(start_point.x + 300, start_point.y - 200), start_length);

    createUI();

    return true;
}

void TreeScene::createStartStructure(cocos2d::Vec2 center_point, float half_width) {
    auto left_bottom = TreeNode::create();
    left_bottom->setPosition(center_point.x - half_width, center_point.y - half_width);
    addChild(left_bottom, left_bottom->getScenePriority());
    left_bottom->getPhysicsBody()->setDynamic(false);

    auto right_bottom = TreeNode::create();
    right_bottom->setPosition(center_point.x + half_width, center_point.y - half_width);
    addChild(right_bottom, left_bottom->getScenePriority());
    right_bottom->getPhysicsBody()->setDynamic(false);

    auto right_top = TreeNode::create();
    right_top->setPosition(center_point.x + half_width, center_point.y + half_width);
    addChild(right_top, left_bottom->getScenePriority());


    right_top->getPhysicsBody()->setVelocity(cocos2d::Vec2(300, 300));

    auto left_top = TreeNode::create();
    left_top->setPosition(center_point.x - half_width, center_point.y + half_width);
    addChild(left_top, left_bottom->getScenePriority());


    auto edge_1 = TreeEdge::create(left_bottom, right_bottom);
    addChild(edge_1, edge_1->getScenePriority());
    //this->_physicsWorld->addJoint(edge_1->getSpring()); PhysicsJoint is not added cos both adjoined nodes are static

    auto edge_2 = TreeEdge::create(right_bottom, right_top);
    addChild(edge_2, edge_2->getScenePriority());
    getPhysicsWorld()->addJoint(edge_2->getSpring());

    auto edge_3 = TreeEdge::create(right_top, left_top);
    addChild(edge_3, edge_3->getScenePriority());
    getPhysicsWorld()->addJoint(edge_3->getSpring());

    auto edge_4 = TreeEdge::create(left_top, left_bottom);
    addChild(edge_4, edge_4->getScenePriority());
    getPhysicsWorld()->addJoint(edge_4->getSpring());

    auto edge_5 = TreeEdge::create(left_bottom, right_top);
    addChild(edge_5, edge_5->getScenePriority());
    getPhysicsWorld()->addJoint(edge_5->getSpring());

    auto edge_6 = TreeEdge::create(right_bottom, left_top);
    addChild(edge_6, edge_6->getScenePriority());
    getPhysicsWorld()->addJoint(edge_6->getSpring());
}

void TreeScene::createUI() {
    auto temp = DebugUI::create();
    temp->setPosition(0, 0);
    temp->setLeftPlayerScore(score_management::ScoreManager::getInstance().getPlayer1Score());
    temp->setRightPlayerScore(score_management::ScoreManager::getInstance().getPlayer2Score());
    addChild(temp, 100);
}

void TreeScene::addNode(cocos2d::EventMouse* event, cocos2d::Scene* scene_ptr) {
    auto new_node = TreeNode::create();
    new_node->setPosition(event->getLocationInView());

    auto factory = EdgeFactory::getInstance();
    factory.setPrototype(TreeEdge::create());

    //auto e = tree_events::TreeNodeCreationEvent(new_node, scene_ptr, &factory);

    //Director::getInstance()->getEventDispatcher()->dispatchEvent(&e);
}

void TreeScene::addEvents() {}
