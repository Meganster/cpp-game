//
// Created by artem on 21.10.16.
//

#ifndef MYGAME_TREESCENE_H
#define MYGAME_TREESCENE_H

#include "cocos2d.h"
#include "TreeParts/NodeFunctionality/TreeNode.h"
#include "managers/TreeManagement/TreeManager.h"
#include "./TreeParts/EdgeFunctionality/TreeEdge.h"


class TreeScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();


    virtual bool init();

    CREATE_FUNC(TreeScene);

private:
    void addEvents();

    tree_management::TreeManager manager;
    std::set<TreeNode*> chosen_tree_nodes;
};


#endif //MYGAME_TREESCENE_H