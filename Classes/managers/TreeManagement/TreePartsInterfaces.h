//
// Created by artem on 22.11.16.
//

#ifndef MYGAME_TREEOBJECTINTERFACES_H
#define MYGAME_TREEOBJECTINTERFACES_H

#include "cocos2d.h"
#include "../ScoreManagement/Scorable.h"
#include "../../event_system/EventWrappers.h"
#include <vector>

namespace tree_interfaces {

    class TreePart: public cocos2d::Sprite, public Scorable {
    public:
        virtual void setPhantom() = 0;

        virtual void setReal() = 0;

        virtual TreePart* getClone() = 0;
    };


    class TreeNodeInterface: public TreePart {    };

    class TreeEdgeInterface: public TreePart {
    public:
        virtual std::vector<TreeNodeInterface*> getNodes() = 0;

        virtual void setPosition(cocos2d::Vec2, cocos2d::Vec2) = 0;
    };
}

#endif //MYGAME_TREEOBJECTINTERFACES_H
