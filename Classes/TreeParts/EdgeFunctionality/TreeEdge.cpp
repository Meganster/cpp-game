//
// Created by yury on 23.11.16.
//

#include "TreeEdge.h"
#include <iostream>
#include <cmath>

std::string TreeEdge::kSpritePath = "wooden_plank.png";
//const std::map<int, Cost> TreeEdge::specificCost; // need to record specificCost!

TreeEdge::TreeEdge(tree_interfaces::TreeNodeInterface* node_1, tree_interfaces::TreeNodeInterface* node_2):
        node_1_{node_1}, node_2_{node_2}, rigidity_{0} {};

TreeEdge::~TreeEdge(){}

TreeEdge* TreeEdge::create(tree_interfaces::TreeNodeInterface* node_1, tree_interfaces::TreeNodeInterface* node_2) {
    if (node_1 != nullptr && node_2 != nullptr) {
        TreeEdge* edge_ptr = new TreeEdge(node_1, node_2);

        if (edge_ptr->initWithFile(TreeEdge::kSpritePath)) {
            edge_ptr->autorelease();
            edge_ptr->initOptions();
            edge_ptr->addEvents();

            edge_ptr->setSpring(cocos2d::PhysicsJointSpring::construct(node_1->getPhysicsBody(), node_2->getPhysicsBody(),
                                                                       node_1->getAnchorPoint(), node_2->getAnchorPoint(),
                                                                       10, 1));  //TODO refactor (just test)

            return edge_ptr;
        } else {
            CC_SAFE_DELETE(edge_ptr);
            return nullptr;
        }
    }

    return nullptr;
}

TreeEdge* TreeEdge::create() {
    return TreeEdge::create(nullptr, nullptr);
}

std::vector<tree_interfaces::TreeNodeInterface*> TreeEdge::getNodes(){
    std::vector<tree_interfaces::TreeNodeInterface*> adjoinedNode;
    adjoinedNode.push_back(node_1_);
    adjoinedNode.push_back(node_2_);

    return adjoinedNode;
};

void TreeEdge::setNodes(tree_interfaces::TreeNodeInterface * node_1, tree_interfaces::TreeNodeInterface * node_2) {
    node_1_ = node_1;
    node_2_ = node_2;

    initOptions();
}


// need to work with this
void TreeEdge::setPhantom() {
}

void TreeEdge::setReal() {
    // need to change here sprite
}


tree_interfaces::TreeEdgeInterface* TreeEdge::getClone(tree_interfaces::TreeNodeInterface* node1,
                                                       tree_interfaces::TreeNodeInterface* node2) {
    TreeEdge* newEdge = TreeEdge::create(node1, node2);
    newEdge->setPhantom();

    return newEdge;
}

score_type TreeEdge::getBuyPrice() const {
    return 1;
}

score_type TreeEdge::getSellPrice() const {
    return 1;
}

void TreeEdge::initOptions() {
    if (node_1_ != nullptr && node_2_ != nullptr) {
        setRotation(countAngle());
        setPosition(countPosition());
        setScaleX(countLength() / getTexture()->getPixelsWide());
        setScaleY(0.1);
    }
}

void TreeEdge::addEvents() {}

float TreeEdge::countAngle(){
    // Need to check coordinate system
    auto dir = node_2_->getPosition() - node_1_->getPosition();
    auto x_dir = cocos2d::Vec2(1, 0);
    return (float)(dir.getAngle(x_dir) * 180 / M_PI);
}

float TreeEdge::countLength() {
    return (node_2_->getPosition() - node_1_->getPosition()).getLength();
}

cocos2d::Vec2 TreeEdge::countPosition(){
    return (node_2_->getPosition() + node_1_->getPosition()) / 2;
}

