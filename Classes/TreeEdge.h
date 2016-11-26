//
// Created by yury on 23.11.16.
//

#ifndef MYGAME_TREEEDGE_H
#define MYGAME_TREEEDGE_H

#include "cocos2d.h"
#include <vector>
#include <map>
#include <string>
#include <Scorable.h>

struct Cost {
    // need check type
    // may be it's 'score_type' ?
    double CostForSold;
    double CostForBuying;

    cost(double costSold, double costBuying){
        costForSold = costSold;
        costForBuying = costBuying;
    }
};

class TreeEdge : public Scorable, TreeEdgeInterface, cocos2d::Sprite {
public:
    TreeEdge(TreeNode node1, TreeNode node2);
    ~TreeEdge();

    vector<TreeNode> getNode(){
        vector<TreeNode> adjoinedNode;
        adjoinedNode.push_back(leftNode);
        adjoinedNode.push_back(rightNode);

        return adjoinedNode;
    };

    const static std::string kSpritePath;
    const static std::map<int, Cost> runningMeter;

private:
    static bool createAttachedTreeEdge();
    double countAngle();
    cocos2d::Vec2& countPosition();

    TreeNode leftNode_, rightNode_;
    double lenght_;
    double rigidity_;   //parameter from physics
};


#endif //MYGAME_TREEEDGE_H
