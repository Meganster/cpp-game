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
#include "ControlZone.h"
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

    private:
        void addChange(TreeChange);

        void addEvents();

        void manageTreeNodeCreationEvent(tree_events::TreeNodeCreationEvent*);

        void manageTreeEdgeCreationEvent(tree_events::TreeEdgeCreationEvent*);

        void manageTreeEdgeDeletionEvent(tree_events::TreeEdgeDeletionEvent*);

        void manageForceApplyingEvent(tree_events::ForceApplyingEvent*);

        void manageRevertChangeEvent(tree_events::RevertLastChangeEvent*);

        void manageSubmitChangesEvent(tree_events::SubmitChangesEvent*);

        bool is_active;
        std::stack<TreeChange> tree_changes;
    };


    class TreeManagerHolder {
    public:
        TreeManagerHolder(cocos2d::Scene *scene);

        std::shared_ptr<TreeManager> getActiveManager();
        std::shared_ptr<TreeManager> getPassiveManager();

        void makeTurn();

        std::shared_ptr<TreeManager> getFirstManager();
        std::shared_ptr<TreeManager> getSecondManager();

    private:
        void manageTreeNodeCreationEvent(tree_events::TreeNodeCreationEvent *event);
        void manageForceApplyingEvent(tree_events::ForceApplyingEvent *event);
        void manageTreeEdgeCreationEvent(tree_events::TreeEdgeCreationEvent* event);
        void manageTreeEdgeDeletionEvent(tree_events::TreeEdgeDeletionEvent* event);

        void manageRevertChangeEvent(tree_events::RevertLastChangeEvent* event);
        void manageSubmitChangesEvent(tree_events::SubmitChangesEvent* event);

        void addEvents();

        std::shared_ptr<TreeManager> manager_1;
        std::shared_ptr<TreeManager> manager_2;

        ControlZone* control_zone_1;
        ControlZone* control_zone_2;
    };

}


#endif //MYGAME_TREEMANAGEMENT_H
