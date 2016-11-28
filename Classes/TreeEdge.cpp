//
// Created by yury on 23.11.16.
//

#include "TreeEdge.h"
#include <iostream>
#include <cmath>

const std::string TreeEdge::kSpritePath = "plank.png";
//const std::map<int, Cost> TreeEdge::runningMeter; // need to record runningMeter!

TreeEdge::TreeEdge(TreeNode* node1, TreeNode* node2){
    if(node1->getPosition().x < node2->getPosition().x) {
        leftNode_ = node1;
        rightNode_ = node2;
    } else{
        leftNode_ = node2;
        rightNode_ = node1;
    }

    lenght_ = sqrt((node1->getPosition().x - node2->getPosition().x)^2 + (node1->getPosition().y - node2->getPosition().y)^2);
    rigidity_ = 0;

    if( createAttachedTreeEdge() ){
        std::cout<<"Edge created!"<<std::endl;
    } else{
        std::cout<<"Error with creating sprite!"<<std::endl;
    }
}

TreeEdge::TreeEdge(cocos2d::Vec2 coordinate_of_begin, cocos2d::Vec2 coordinate_of_end){
    leftNode_ = new TreeNode();
    rightNode_ = new TreeNode();

    if(coordinate_of_begin.x < coordinate_of_end.x) {
        leftNode_->setPosition(coordinate_of_begin);
        rightNode_->setPosition(coordinate_of_end);
    } else{
        leftNode_->setPosition(coordinate_of_end);
        rightNode_->setPosition(coordinate_of_begin);
    }

    lenght_ = sqrt((coordinate_of_begin.x - coordinate_of_end.x)^2 + (coordinate_of_begin.y - coordinate_of_end.y)^2);
    rigidity_ = 0;

    if( createAttachedTreeEdge() ){
        std::cout<<"Edge created!"<<std::endl;
    } else{
        std::cout<<"Error with creating sprite!"<<std::endl;
    }
}

TreeEdge::~TreeEdge(){}

std::vector<TreeNode*> TreeEdge::getNodes(){
    std::vector<TreeNode*> adjoinedNode;
    adjoinedNode.push_back(leftNode);
    adjoinedNode.push_back(rightNode);

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
//

TreeEdge* TreeEdge::getClone(TreeNode* node1, TreeNode* node2) {
    TreeEdge* newEdge = new TreeEdge(node1, node2);
    newEdge->setPhantom();

    return newEdge;
}


double TreeEdge::countAngle(){
    return acos( abs(leftNode_->y - rightNode_->y) / lenght_ ) * 180.0 / M_PI;
}

cocos2d::Vec2 TreeEdge::countPosition(){
    return cocos2d::Vec2(abs(rightNode_->x - leftNode_->x)/2, abs(rightNode_->y - leftNode_->y)/2);
}

static bool TreeEdge::createAttachedTreeEdge(){
    TreeEdge* edge_ptr = new TreeEdge();

    if (edge_ptr->initWithFile(TreeEdge::kSpritePath)) {
        edge_ptr->autorelease();
        edge_ptr->setPosition( countPosition() );
        edge_ptr->setRotation( countAngle() );
        edge_ptr->setScaleX(lenght_ / 377); // may be some problem with scale!!!

        return true;
    }
    else {
        CC_SAFE_DELETE(edge_ptr);
        return false;
    }
}

