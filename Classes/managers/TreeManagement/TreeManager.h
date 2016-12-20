//
// Created by artem on 13.11.16.
//

#ifndef MYGAME_TREEMANAGEMENT_H
#define MYGAME_TREEMANAGEMENT_H

#include "cocos2d.h"
#include "../../event_system/EventWrappers.h"
#include "TreePartsInterfaces.h"
#include "TreeEvents.h"
#include "TreePartsCreation.h"
#include <set>
#include <memory>

namespace tree_management {

    class TreeChange {
    public:
        TreeChange() = default;

        void addTreePart(tree_interfaces::TreePart*);

        void revert();

        void submit();
    private:
        std::vector<tree_interfaces::TreePart*> tree_parts;
    };

    class TreeManager {
    public:

        friend class TreeManagerHolder;

        TreeManager(cocos2d::Rect);

        void switchState();

        void setActive();

        void setPassive();

        bool isActive();

        bool revertLastChange();

        void submitChanges();

        bool controlsPoint(cocos2d::Vec2 point) {
            return control_area_.containsPoint(point);
        };

    private:
        void addChange(TreeChange);

        void selectNode(tree_interfaces::TreeNodeInterface*);

        void deselectNode(tree_interfaces::TreeNodeInterface*);

        void addEvents();

        void manageTreeNodeCreationEvent(tree_events::TreeNodeCreationEvent*);

        void manageTreeNodeSelectionEvent(tree_events::TreeNodeSelectionEvent*);

        void manageTreeNodeDeselectionEvent(tree_events::TreeNodeDeselectionEvent*);

        void manageTreeEdgeCreationEvent(tree_events::TreeEdgeCreationEvent*);

        void manageTreeEdgeDeletionEvent(tree_events::TreeEdgeDeletionEvent*);

        void manageRevertChangeEvent(tree_events::RevertLastChangeEvent*);

        void manageSubmitChangesEvent(tree_events::SubmitChangesEvent*);

        bool is_active;
        cocos2d::Rect control_area_;
        std::set<tree_interfaces::TreeNodeInterface*> selected_nodes;
        std::stack<TreeChange> tree_changes;
    };

    class TreeManagerHolder {
    public:
        TreeManagerHolder(std::shared_ptr<TreeManager>, std::shared_ptr<TreeManager>);

        //TreeManagerHolder();

        TreeManagerHolder() {
            auto visible_size = cocos2d::Director::getInstance()->getVisibleSize();
            auto left_rect = cocos2d::Rect(0, 0, visible_size.width / 2, visible_size.height);
            auto right_rect = cocos2d::Rect(visible_size.width / 2, 0, visible_size.width / 2, visible_size.height);

            manager_1 = std::shared_ptr<TreeManager>(new TreeManager(left_rect));
            manager_1->setActive();

            manager_2 = std::shared_ptr<TreeManager>(new TreeManager(right_rect));
            manager_2->setPassive();

            addEvents();
        }

        std::shared_ptr<TreeManager> getActiveManager();

        std::shared_ptr<TreeManager> getPassiveManager();

        void switchManagers();

        std::shared_ptr<TreeManager> getFirstManager();

        std::shared_ptr<TreeManager> getSecondManager();

    private:
        void manageTreeNodeCreationEvent(tree_events::TreeNodeCreationEvent* event) {
            auto active_manager = getActiveManager();
            if (active_manager->controlsPoint(event->new_node->getPosition())) {
                active_manager->manageTreeNodeCreationEvent(event);
            }
        };

        void manageTreeNodeSelectionEvent(tree_events::TreeNodeSelectionEvent* event) {
            auto active_manager = getActiveManager();

            if (active_manager->controlsPoint(event->selected_node->getPosition())) {
                active_manager->manageTreeNodeSelectionEvent(event);
            }
        };

        void manageTreeNodeDeselectionEvent(tree_events::TreeNodeDeselectionEvent* event) {
            auto active_manager = getActiveManager();
            if (active_manager->controlsPoint(event->deselected_node->getPosition())) {
                active_manager->manageTreeNodeDeselectionEvent(event);
            }
        };

        void manageTreeEdgeCreationEvent(tree_events::TreeEdgeCreationEvent* event) {
            auto active_manager = getActiveManager();
            if (active_manager->controlsPoint(event->tree_node_1->getPosition()) &&
                    active_manager->controlsPoint(event->tree_node_2->getPosition())) {
                active_manager->manageTreeEdgeCreationEvent(event);
            }
        };

        void manageTreeEdgeDeletionEvent(tree_events::TreeEdgeDeletionEvent* event) {
            getActiveManager()->manageTreeEdgeDeletionEvent(event);
        };

        void manageRevertChangeEvent(tree_events::RevertLastChangeEvent* event) {
            getActiveManager()->manageRevertChangeEvent(event);
        };

        void manageSubmitChangesEvent(tree_events::SubmitChangesEvent* event) {
            getActiveManager()->manageSubmitChangesEvent(event);
            switchManagers();
        };

        void addEvents() {
            auto revert_change_call_back = [this](tree_events::RevertLastChangeEvent* event) -> void  {
                manageRevertChangeEvent(event);
            };
            auto revert_change_listener = event_wrappers::create_listener<tree_events::RevertLastChangeEvent>(revert_change_call_back);
            cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(revert_change_listener, 1);

            auto submit_call_back = [this](tree_events::SubmitChangesEvent* event) -> void {
                manageSubmitChangesEvent(event);
            };
            auto submit_changes_listener = event_wrappers::create_listener<tree_events::SubmitChangesEvent>(submit_call_back);
            cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(submit_changes_listener, 1);

            auto node_selected_call_back = [this](tree_events::TreeNodeSelectionEvent* event) -> void {
                manageTreeNodeSelectionEvent(event);
            };
            auto node_selected_listener = event_wrappers::create_listener<tree_events::TreeNodeSelectionEvent>(node_selected_call_back);
            cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(node_selected_listener, 1);


            auto node_deselected_call_back = [this](tree_events::TreeNodeDeselectionEvent* event) -> void {
                manageTreeNodeDeselectionEvent(event);
            };
            auto node_deselected_listener = event_wrappers::create_listener<tree_events::TreeNodeDeselectionEvent>(node_deselected_call_back);
            cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(node_deselected_listener, 1);


            auto node_created_call_back = [this](tree_events::TreeNodeCreationEvent* event) -> void {
                manageTreeNodeCreationEvent(event);
            };
            auto node_created_listener = event_wrappers::create_listener<tree_events::TreeNodeCreationEvent>(node_created_call_back);
            cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(node_created_listener, 1);


            auto edge_created_call_back = [this](tree_events::TreeEdgeCreationEvent* event) -> void {
                manageTreeEdgeCreationEvent(event);
            };
            auto edge_created_listener = event_wrappers::create_listener<tree_events::TreeEdgeCreationEvent>(edge_created_call_back);
            cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(edge_created_listener, 1);


            auto edge_deleted_call_back = [this](tree_events::TreeEdgeDeletionEvent* event) -> void {
                manageTreeEdgeDeletionEvent(event);
            };
            auto edge_deleted_listener = event_wrappers::create_listener<tree_events::TreeEdgeDeletionEvent>(edge_deleted_call_back);
            cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(edge_deleted_listener, 1);
        }

        std::shared_ptr<TreeManager> manager_1;
        std::shared_ptr<TreeManager> manager_2;
    };

}


#endif //MYGAME_TREEMANAGEMENT_H
