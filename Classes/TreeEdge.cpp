//
// Created by yury on 23.11.16.
//

#include "TreeEdge.h"
#include <iostream>
#include <cmath>

const std::string TreeEdge::kSpritePath = "plank.png";
//const std::map<int, Cost> TreeEdge::runningMeter; // need to record runningMeter!

TreeEdge::TreeEdge(TreeNode& node1, TreeNode& node2){
    if(node1.x < node2.x) {
        leftNode_ = node1;
        rightNode_ = node2;
    } else{
        leftNode_ = node2;
        rightNode_ = node1;
    }

    lenght_ = sqrt((node1.x - node2.x)^2 + (node1.y - node2.y)^2);
    rigidity_ = 0;
}

TreeEdge::~TreeEdge(){
    this->removeFromParentAndCleanup(true);
}

double TreeEdge::countAngle(){
    return acos( abs(leftNode_.y - rightNode_.y) / lenght_ ) * 180.0 / M_PI;
}

cocos2d::Vec2& TreeEdge::countPosition(){
    return cocos2d::Vec2(abs(rightNode_.x - leftNode_.x)/2, abs(rightNode_.y - leftNode_.y)/2);
}

static bool TreeEdge::createAttachedTreeEdge(){
    TreeEdge* edge_ptr = new TreeEdge();

    if (edge_ptr->initWithFile(TreeEdge::kSpritePath)) {
        edge_ptr->autorelease();
        edge_ptr->setPosition( countPosition() );
        edge_ptr->setRotation( countAngle() );
        edge_ptr->setScaleX(lenght_ / lenght_); // problem with scale!!!

        return true;
    }
    else {
        CC_SAFE_DELETE(edge_ptr);
        return false;
    }
}

