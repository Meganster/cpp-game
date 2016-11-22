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

    class TreeNodeInterface: public cocos2d::Sprite {};

    class TreeEdgeInterface: public cocos2d::Sprite, Scorable {
        virtual std::vector<TreeNodeInterface*> getNodes() = 0;
    };

    class EdgeFactoryInterface: public Scorable {
    public:
        virtual static EdgeFactoryInterface& getInstance() = 0;

        virtual void setSample(TreeEdgeInterface* ) = 0;

        virtual TreeEdgeInterface* getNewEdge(TreeNodeInterface*, TreeNodeInterface*) = 0;
    };
}

namespace tree_events {

    class TreeEdgeCreationEvent: public event_wrappers::MyEventCustom {
    public:
        TreeEdgeCreationEvent(tree_interfaces::TreeNodeInterface*, tree_interfaces::TreeNodeInterface*,
                              cocos2d::Node*);

        static const std::string kEventName;

        cocos2d::Node* parent_node;
        tree_interfaces::TreeNodeInterface* tree_node_1;
        tree_interfaces::TreeNodeInterface* tree_node_2;
    };

    class TreeEdgeDeletionEvent: public event_wrappers::MyEventCustom {
    public:
        TreeEdgeDeletionEvent(tree_interfaces::TreeEdgeInterface*, cocos2d::Node*);

        static const std::string kEventName;

        cocos2d::Node* parent_node;
        tree_interfaces::TreeEdgeInterface* edge_to_delete;
    };

    class TreeNodeCreationEvent: public event_wrappers::MyEventCustom {
    public:
        TreeNodeCreationEvent(tree_interfaces::TreeNodeInterface*, cocos2d::Node*);

        static const std::string kEventName;

        cocos2d::Node* parent_node;
        tree_interfaces::TreeNodeInterface* new_node;
    };

    class TreeNodeSelectionEvent: public event_wrappers::MyEventCustom {
    public:
        TreeNodeSelectionEvent(tree_interfaces::TreeNodeInterface*);

        static const std::string kEventName;

        tree_interfaces::TreeNodeInterface* selected_node;
    };

    class TreeNodeDeselectionEvent: public event_wrappers::MyEventCustom {
    public:
        TreeNodeDeselectionEvent(tree_interfaces::TreeNodeInterface*);

        static const std::string kEventName;

        tree_interfaces::TreeNodeInterface* deselected_node;
    };
}

#endif //MYGAME_TREEOBJECTINTERFACES_H
