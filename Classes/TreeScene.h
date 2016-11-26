//
// Created by artem on 21.10.16.
//

#ifndef MYGAME_TREESCENE_H
#define MYGAME_TREESCENE_H

#include "cocos2d.h"
#include "TreeNode.h"
#include "managers/TreeManagement/TreeManager.h"


class TreeScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();


    virtual bool init();

    CREATE_FUNC(TreeScene);

private:
    void addEvents();

    tree_management::TreeManager manager;

    static void treeNodeSelectedCallback(TreeNodeSelectedEvent*, TreeScene*);
    std::set<TreeNode*> chosen_tree_nodes;
};


#endif //MYGAME_TREESCENE_H