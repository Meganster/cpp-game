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
        TreeManager();

        void switchState();

        void setActive();

        void setPassive();

        bool isActive();

        bool revertLastChange();

        void submitChanges();

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
        std::set<tree_interfaces::TreeNodeInterface*> selected_nodes;
        std::stack<TreeChange> tree_changes;
    };

    class TreeManagerHolder {
    public:
        TreeManagerHolder(std::shared_ptr<TreeManager>, std::shared_ptr<TreeManager>);

        std::shared_ptr<TreeManager> getActiveManager();

        std::shared_ptr<TreeManager> getPassiveManager();

        void switchManagers();

        std::shared_ptr<TreeManager> getFirstManager();

        std::shared_ptr<TreeManager> getSecondManager();

    private:
        std::shared_ptr<TreeManager> manager_1;
        std::shared_ptr<TreeManager> manager_2;
    };

}


#endif //MYGAME_TREEMANAGEMENT_H
