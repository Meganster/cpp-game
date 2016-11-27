//
// Created by yury on 23.11.16.
//

#ifndef MYGAME_TREEEDGE_H
#define MYGAME_TREEEDGE_H

#include "cocos2d.h"
#include <vector>
#include <map>
#include <string>
#include "./managers/TreeManagement/TreePartsInterfaces.h"
#include "./TreeNode.h"

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

class TreeEdge : public tree_interfaces::TreeEdgeInterface {
public:
    TreeEdge(TreeNode* node1, TreeNode* node2);
    ~TreeEdge();

    std::vector<TreeNode*> getNodes();
    void setPhantom();
    void setReal();
    tree_interfaces::TreePart* getClone();


    const static std::string kSpritePath;
    const static std::map<int, Cost> runningMeter;

private:
    static bool createAttachedTreeEdge();
    double countAngle();
    cocos2d::Vec2& countPosition();

    TreeNode* leftNode_;
    TreeNode* rightNode_;
    double lenght_;
    double rigidity_;   //parameter from physics
};


#endif //MYGAME_TREEEDGE_H
