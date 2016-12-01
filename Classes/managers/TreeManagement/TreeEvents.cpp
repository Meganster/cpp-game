//
// Created by artem on 11/26/16.
//

#include "TreeEvents.h"

using namespace tree_events;
using namespace tree_interfaces;
using namespace tree_part_creation;


RevertLastChangeEvent::RevertLastChangeEvent(): MyEventCustom(this) {};

const std::string RevertLastChangeEvent::kEventName = "RevertLastChangeEvent";


SubmitChangesEvent::SubmitChangesEvent(): MyEventCustom(this) {};

const std::string SubmitChangesEvent::kEventName = "SubmitChanges";


TreeEdgeCreationEvent::TreeEdgeCreationEvent(TreeNodeInterface *tree_node_1, TreeNodeInterface *tree_node_2,
                                             cocos2d::Scene *parent_node, EdgeFactoryInterface* edge_factory) :
        MyEventCustom{this}, tree_node_1{tree_node_1}, tree_node_2{tree_node_2},
        scene{parent_node}, edge_factory{edge_factory} {};

const std::string TreeEdgeCreationEvent::kEventName = "TreeEdgeCreationEvent";


TreeNodeCreationEvent::TreeNodeCreationEvent(TreeNodeInterface *new_node, cocos2d::Scene *parent_node,
                                             EdgeFactoryInterface *edge_factory):
        MyEventCustom{this}, new_node{new_node}, edge_factory{edge_factory}, scene{parent_node} {};

const std::string TreeNodeCreationEvent::kEventName = "TreeNodeCreationEvent";


TreeEdgeDeletionEvent::TreeEdgeDeletionEvent(TreeEdgeInterface *edge_to_delete,
                                             cocos2d::Scene *parent_node):
        MyEventCustom{this}, edge_to_delete{edge_to_delete}, scene{parent_node} {};

const std::string TreeEdgeDeletionEvent::kEventName = "TreeEdgeDeletionEvent";


TreeNodeSelectionEvent::TreeNodeSelectionEvent(TreeNodeInterface* selected_node):
        MyEventCustom{this}, selected_node{selected_node} {};

const std::string TreeNodeSelectionEvent::kEventName = "TreeNodeSelectionEvent";


TreeNodeDeselectionEvent::TreeNodeDeselectionEvent(TreeNodeInterface* deselected_node):
        MyEventCustom{this}, deselected_node{deselected_node} {};

const std::string TreeNodeDeselectionEvent::kEventName = "TreeNodeDeselectionEvent";

