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
    void Add() { adding = false; };

    virtual bool init();

    CREATE_FUNC(TreeScene);

private:
    void addEvents();

    static void addNode(cocos2d::EventMouse*, cocos2d::Scene*);

    tree_management::TreeManagerHolder holder;

    bool adding;
};


#endif //MYGAME_TREESCENE_H