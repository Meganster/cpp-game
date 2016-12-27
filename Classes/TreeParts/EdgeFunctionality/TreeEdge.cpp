//
// Created by yury on 23.11.16.
//

#include "TreeEdge.h"
#include <iostream>
#include <cmath>

std::string TreeEdge::kSpritePath = "wooden_plank.png";
//const std::map<int, Cost> TreeEdge::specificCost; // need to record specificCost!

TreeEdge::TreeEdge(tree_interfaces::TreeNodeInterface *node_1, tree_interfaces::TreeNodeInterface *node_2,
                   float stiffness, float damping, float max_force) :
        node_1_{node_1}, node_2_{node_2}, stiffness_{stiffness}, damping_{damping}, max_force_{max_force} {};

TreeEdge* TreeEdge::create(tree_interfaces::TreeNodeInterface* node_1, tree_interfaces::TreeNodeInterface* node_2,
                           float stiffness, float damping, float max_force) {
    TreeEdge* edge_ptr = new TreeEdge(node_1, node_2, stiffness, damping, max_force);

    if (node_1 != nullptr && node_2 != nullptr) {
        if (edge_ptr->initWithFile(TreeEdge::kSpritePath)) {
            edge_ptr->autorelease();
            edge_ptr->initOptions();
            edge_ptr->addEvents();

            return edge_ptr;
        } else {
            CC_SAFE_DELETE(edge_ptr);
            return nullptr;
        }
    }

    return edge_ptr;
}

TreeEdge* TreeEdge::create(tree_interfaces::TreeNodeInterface* node_1, tree_interfaces::TreeNodeInterface* node_2) {
    return TreeEdge::create(node_1, node_2,
                            TreeEdge::default_stiffness, TreeEdge::default_damping, TreeEdge::default_max_force);
}

TreeEdge* TreeEdge::create() {
    auto result = TreeEdge::create(nullptr, nullptr);
    return result;
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
    TreeEdge* newEdge = TreeEdge::create(node1, node2, stiffness_, damping_, max_force_);
    newEdge->setPhantom();

    return newEdge;
}

score_type TreeEdge::getBuyPrice() const {
    return 1;
}

score_type TreeEdge::getSellPrice() const {
    return 1;
}

void TreeEdge::destroy() {
    std::cout << "Destroy" << std::endl;

    if (node_1_->getPhysicsBody()->getJoints().size() == 1) {
        node_1_->removeFromParentAndCleanup(true);
    }

    if (node_2_->getPhysicsBody()->getJoints().size() == 1) {
        node_2_->removeFromParentAndCleanup(true);
    }

    spring_->removeFormWorld();

    removeFromParentAndCleanup(true);
}

void TreeEdge::initOptions() {
    if (node_1_ != nullptr && node_2_ != nullptr) {
        auto spring = cocos2d::PhysicsJointSpring::construct(node_1_->getPhysicsBody(), node_2_->getPhysicsBody(),
                                                             node_1_->getAnchorPoint(), node_2_->getAnchorPoint(),
                                                             stiffness_, damping_);
        setSpring(spring);
        init_length_ = (node_1_->getPosition() - node_2_->getPosition()).length();

        auto body = cocos2d::PhysicsBody::create(); // this body is necessary to enable update() usage
        body->setDynamic(false);
        setPhysicsBody(body);

        updateEdgePosition();
    }
}

void TreeEdge::addEvents() {}

void TreeEdge::removeEdge() {
    std::cout << "Time to break: " << getSpringForce() << "  " << max_force_ << std::endl;

    auto e = tree_events::TreeEdgeDeletionEvent(this);
    _eventDispatcher->dispatchEvent(&e);
}

void TreeEdge::update(float) {
    if (node_1_ != nullptr && node_2_ != nullptr) {
        updateEdgePosition();

        if (getSpringForce() > max_force_) {
            removeEdge();
        }
    }
}

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

void TreeEdge::updateEdgePosition() {
    setRotation(countAngle());
    setPosition(countPosition());
    setScaleX(countLength() / getTexture()->getPixelsWide());
    setScaleY(0.1f);
}

float TreeEdge::getSpringLength() {
    return (node_1_->getPosition() - node_2_->getPosition()).length();
}

float TreeEdge::getSpringForce() {
    return std::abs(stiffness_ * (getSpringLength() - init_length_));
}

