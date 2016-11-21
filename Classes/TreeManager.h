//
// Created by artem on 13.11.16.
//

#ifndef MYGAME_TREEMANAGER_H
#define MYGAME_TREEMANAGER_H

#include "cocos2d.h"
#include "event_wrappers.h"
#include "TreeNode.h"

class CreateEdgeRequest;
class DeleteEdgeRequest;

class TreeManager: public cocos2d::Sprite {
public:
    TreeManager();

    ~TreeManager();

    static TreeManager* create();
private:
    void createEdge(CreateEdgeRequest*);

    void deleteEdge(DeleteEdgeRequest*);

    void initOptions();

    void addEvents();

};



#endif //MYGAME_TREEMANAGER_H
