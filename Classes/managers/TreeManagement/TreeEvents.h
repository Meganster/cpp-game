//
// Created by artem on 11/26/16.
//

#ifndef MYGAME_TREEEVENTS_H
#define MYGAME_TREEEVENTS_H

#include "cocos2d.h"
#include "TreePartsInterfaces.h"

namespace tree_events {

    class TreeEdgeCreationEvent: public event_wrappers::MyEventCustom {
    public:
        TreeEdgeCreationEvent(tree_interfaces::TreeNodeInterface *, tree_interfaces::TreeNodeInterface *,
                              tree_interfaces::EdgeFactoryInterface*, cocos2d::Scene *);

        static const std::string kEventName;

        cocos2d::Scene* scene;
        tree_interfaces::EdgeFactoryInterface* edge_factory;
        tree_interfaces::TreeNodeInterface* tree_node_1;
        tree_interfaces::TreeNodeInterface* tree_node_2;
    };

    class TreeEdgeDeletionEvent: public event_wrappers::MyEventCustom {
    public:
        TreeEdgeDeletionEvent(tree_interfaces::TreeEdgeInterface *, cocos2d::Scene *);

        static const std::string kEventName;

        cocos2d::Scene* scene;
        tree_interfaces::TreeEdgeInterface* edge_to_delete;
    };

    class TreeNodeCreationEvent: public event_wrappers::MyEventCustom {
    public:
        TreeNodeCreationEvent(cocos2d::Vec2, tree_interfaces::EdgeFactoryInterface*, cocos2d::Scene *);

        static const std::string kEventName;

        cocos2d::Scene* scene;
        tree_interfaces::EdgeFactoryInterface* edge_factory;
        cocos2d::Vec2 new_node_coord;
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

#endif //MYGAME_TREEEVENTS_H
