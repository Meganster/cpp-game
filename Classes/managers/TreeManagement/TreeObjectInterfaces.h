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

    class TreePart: public cocos2d::Sprite, public Scorable {};

    class TreeNodeInterface: public TreePart {};

    class TreeEdgeInterface: public TreePart {
    public:
        virtual std::vector<TreeNodeInterface*> getNodes() = 0;

        virtual void setPosition(cocos2d::Vec2, cocos2d::Vec2) = 0;
    };

    class EdgeFactoryInterface: public Scorable {
    public:
        /**
         * Through this method you set edge sample to factory
         */
        virtual void setSample(TreeEdgeInterface* ) = 0;

        /**
         * Through this method you set request to create one edge
         */
        virtual void setRequest(cocos2d::Vec2, cocos2d::Vec2) = 0;

        /**
         * Through this method you set request to create multiple edges
         */
        virtual void setRequest(cocos2d::Vec2, std::vector<cocos2d::Vec2>&) = 0;

        /**
         * This method returns the clone of sample edge
         */
        virtual std::vector<TreeEdgeInterface*> getEdges() = 0;

        /**
         * This method flushes all inner request structures
         */
        virtual void closeRequest() = 0;
    };
}

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

#endif //MYGAME_TREEOBJECTINTERFACES_H
