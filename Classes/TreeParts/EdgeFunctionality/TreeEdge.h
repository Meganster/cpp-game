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

struct Cost {
    score_type costForSold;
    score_type costForBuying;

    Cost(score_type costSold, score_type costBuying): costForSold{costSold}, costForBuying{costBuying} {}
};

class TreeEdge : public tree_interfaces::TreeEdgeInterface {
public:
    TreeEdge() = delete;

    TreeEdge(tree_interfaces::TreeNodeInterface*, tree_interfaces::TreeNodeInterface*);
    ~TreeEdge();

    int getScenePriority() { return 8; };

    static TreeEdge* create(tree_interfaces::TreeNodeInterface*, tree_interfaces::TreeNodeInterface*);
    static TreeEdge* create();

    std::vector<tree_interfaces::TreeNodeInterface*> getNodes();
    void setNodes(tree_interfaces::TreeNodeInterface*, tree_interfaces::TreeNodeInterface*);

    void setPhantom();
    void setReal();
    tree_interfaces::TreeEdgeInterface* getClone(tree_interfaces::TreeNodeInterface*,
                                                 tree_interfaces::TreeNodeInterface*);
    score_type getBuyPrice() const;
    score_type getSellPrice() const;


    static std::string kSpritePath;
    const static std::map<int, Cost> specificCost;

private:
    void initOptions();
    void addEvents();

    float countAngle();
    float countLength();
    cocos2d::Vec2 countPosition();

    tree_interfaces::TreeNodeInterface* node_1_;
    tree_interfaces::TreeNodeInterface* node_2_;
    float rigidity_;   //parameter from physics
};


#endif //MYGAME_TREEEDGE_H
