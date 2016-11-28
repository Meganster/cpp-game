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
    TreeEdge* edge_ptr = new TreeEdge(node_1, node_2);

    if (edge_ptr->initWithFile(TreeEdge::kSpritePath)) {
        edge_ptr->autorelease();
        edge_ptr->initOptions();
        edge_ptr->addEvents();

        return edge_ptr;
    }

    CC_SAFE_DELETE(edge_ptr);
    return nullptr;
}

std::vector<tree_interfaces::TreeNodeInterface*> TreeEdge::getNodes(){
    std::vector<tree_interfaces::TreeNodeInterface*> adjoinedNode;
    adjoinedNode.push_back(node_1_);
    adjoinedNode.push_back(node_2_);

    return adjoinedNode;
};


// need to work with this
void TreeEdge::setPhantom() {
    kSpritePath = "plank.png";
    // need to change here sprite
}

void TreeEdge::setReal() {
    kSpritePath = "plank_clear1.png";
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
    setRotation(countAngle());
    setPosition(countPosition());
    setScaleX(countLength() / getTexture()->getPixelsWide());
    setScaleY(0.1);
}

void TreeEdge::addEvents() {}

float TreeEdge::countAngle(){
    // Need to check coordinate system
    return -(float)(asin( (node_2_->getPosition().y - node_1_->getPosition().y) / countLength() ) * 180 / M_PI) ;
}

float TreeEdge::countLength() {
    double x_coord_dif = node_2_->getPosition().x - node_1_->getPosition().x;
    double y_coord_dif = node_2_->getPosition().y - node_1_->getPosition().y;
    return sqrt(x_coord_dif * x_coord_dif + y_coord_dif * y_coord_dif);
}

cocos2d::Vec2 TreeEdge::countPosition(){
    return cocos2d::Vec2((node_2_->getPosition().x + node_1_->getPosition().x) / 2,
                         (node_2_->getPosition().y + node_1_->getPosition().y) / 2);
}

