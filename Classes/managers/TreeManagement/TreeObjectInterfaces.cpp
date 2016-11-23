//
// Created by artem on 22.11.16.
//

#include "TreeObjectInterfaces.h"

tree_events::TreeEdgeCreationEvent::TreeEdgeCreationEvent(tree_interfaces::TreeNodeInterface *tree_node_1,
                                                          tree_interfaces::TreeNodeInterface *tree_node_2,
                                                          cocos2d::Scene *parent_node):
        MyEventCustom{this}, tree_node_1{tree_node_1}, tree_node_2{tree_node_2}, scene{parent_node} {};

const std::string tree_events::TreeEdgeCreationEvent::kEventName = "TreeEdgeCreationEvent";


tree_events::TreeNodeCreationEvent::TreeNodeCreationEvent(tree_interfaces::TreeNodeInterface *new_node,
                                                          cocos2d::Scene *parent_node):
        MyEventCustom{this}, new_node{new_node}, scene{parent_node} {};

const std::string tree_events::TreeNodeCreationEvent::kEventName = "TreeNodeCreationEvent";


tree_events::TreeEdgeDeletionEvent::TreeEdgeDeletionEvent(tree_interfaces::TreeEdgeInterface *edge_to_delete,
                                                          cocos2d::Scene *parent_node):
        MyEventCustom{this}, edge_to_delete{edge_to_delete}, scene{parent_node} {};

const std::string tree_events::TreeEdgeDeletionEvent::kEventName = "TreeEdgeDeletionEvent";


tree_events::TreeNodeSelectionEvent::TreeNodeSelectionEvent(tree_interfaces::TreeNodeInterface* selected_node):
        MyEventCustom{this}, selected_node{selected_node} {};

const std::string tree_events::TreeNodeSelectionEvent::kEventName = "TreeNodeSelectionEvent";


tree_events::TreeNodeDeselectionEvent::TreeNodeDeselectionEvent(tree_interfaces::TreeNodeInterface* deselected_node):
        MyEventCustom{this}, deselected_node{deselected_node} {};

const std::string tree_events::TreeNodeDeselectionEvent::kEventName = "TreeNodeDeselectionEvent";