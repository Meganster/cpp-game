//
// Created by artem on 22.11.16.
//

#ifndef MYGAME_TREEOBJECTINTERFACES_H
#define MYGAME_TREEOBJECTINTERFACES_H

#include "cocos2d.h"
#include "../ScoreManagement/Scorable.h"
#include <vector>

namespace tree_interfaces {

    class TreePart: public cocos2d::Sprite, public Scorable {
    public:
        virtual void setPhantom() = 0;

        virtual void setReal() = 0;
<<<<<<< HEAD
=======

        virtual TreeEdge* getClone() = 0;
>>>>>>> 0ab52a6695f2d01f00a55b7c4025e4ae2004731c
    };


    class TreeNodeInterface: public TreePart {
    public:
        virtual void setSelected() = 0;
        virtual void setDeselected() = 0;
        virtual int getScenePriority() = 0;
    };

    class TreeEdgeInterface: public TreePart {
    public:
        virtual int getScenePriority() = 0;
        virtual std::vector<TreeNodeInterface*> getNodes() = 0;
        virtual void setNodes(TreeNodeInterface*, TreeNodeInterface*) = 0;
        virtual TreeEdgeInterface* getClone(TreeNodeInterface*, TreeNodeInterface*) = 0;
    };
}

#endif //MYGAME_TREEOBJECTINTERFACES_H
