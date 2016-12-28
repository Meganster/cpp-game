//
// Created by artem on 11/26/16.
//

#ifndef MYGAME_TREEEVENTS_H
#define MYGAME_TREEEVENTS_H

#include <set>
#include "cocos2d.h"
#include "TreePartsInterfaces.h"
#include "TreePartsCreation.h"
#include "../../event_system/EventWrappers.h"


namespace tree_events {

    class RevertLastChangeEvent: public event_wrappers::MyEventCustom {
    public:
        RevertLastChangeEvent();

        static const std::string kEventName;
    };

    class SubmitChangesEvent: public event_wrappers::MyEventCustom {
    public:
        SubmitChangesEvent();

        static const std::string kEventName;
    };

    class TreeEdgeCreationEvent: public event_wrappers::MyEventCustom {
    public:
        TreeEdgeCreationEvent(tree_interfaces::TreeNodeInterface *, tree_interfaces::TreeNodeInterface *,
                              cocos2d::Scene *, tree_part_creation::EdgeFactoryInterface* factory = nullptr);

        static const std::string kEventName;

        cocos2d::Scene* scene;
        tree_part_creation::EdgeFactoryInterface* edge_factory;
        tree_interfaces::TreeNodeInterface* tree_node_1;
        tree_interfaces::TreeNodeInterface* tree_node_2;
    };

    class TreeEdgeDeletionEvent: public event_wrappers::MyEventCustom {
    public:
        TreeEdgeDeletionEvent(tree_interfaces::TreeEdgeInterface* tree_edge);

        static const std::string kEventName;

        tree_interfaces::TreeEdgeInterface* tree_edge_;
    };

    class TreeNodeCreationEvent: public event_wrappers::MyEventCustom {
    public:
        TreeNodeCreationEvent(TreeNodeInterface *, std::set<TreeNodeInterface*>, cocos2d::Scene *,
                              tree_part_creation::EdgeFactoryInterface *factory = nullptr);

        static const std::string kEventName;

        cocos2d::Scene* scene;
        tree_part_creation::EdgeFactoryInterface* edge_factory;
        TreeNodeInterface* new_node;
        std::set<TreeNodeInterface*> selected_nodes;
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

    class ForceApplyingEvent: public event_wrappers::MyEventCustom {
    public:
        ForceApplyingEvent(TreeNodeInterface *node, tree_interfaces::ForceInterface *force);

        static const std::string kEventName;

        tree_interfaces::ForceInterface* force;
        tree_interfaces::TreeNodeInterface* node;
    };

    class ScoreChangeEvent: public event_wrappers::MyEventCustom {
    public:
        ScoreChangeEvent(int new_score, bool is_active_player_score);

        static const std::string kEventName;

        int new_score;
        bool is_active_player_score;
    };

    class TurnFinishedEvent: public event_wrappers::MyEventCustom {
    public:
        TurnFinishedEvent();
        static const std::string kEventName;
    };
}

#endif //MYGAME_TREEEVENTS_H
