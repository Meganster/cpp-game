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
