//
// Created by artem on 13.11.16.
//

#ifndef MYGAME_TREEMANAGEMENT_H
#define MYGAME_TREEMANAGEMENT_H

#include "cocos2d.h"
#include "../../event_system/EventWrappers.h"
#include "TreeObjectInterfaces.h"
#include <set>
#include <memory>

namespace tree_management {

    class TreeManager {
    public:
        TreeManager();

        TreeManager(bool, std::shared_ptr<tree_interfaces::EdgeFactoryInterface>);

        void switchState();

        void setFactory(std::shared_ptr<tree_interfaces::EdgeFactoryInterface>);

        void setActive();

        void setPassive();

        bool isActive();

    private:

        void selectNode(tree_interfaces::TreeNodeInterface*);

        void deselectNode(tree_interfaces::TreeNodeInterface*);

        void addEvents();

        void manageTreeNodeCreationEvent(tree_events::TreeNodeCreationEvent*);

        void manageTreeNodeSelectionEvent(tree_events::TreeNodeSelectionEvent*);

        void manageTreeNodeDeselectionEvent(tree_events::TreeNodeDeselectionEvent*);

        void manageTreeEdgeCreationEvent(tree_events::TreeEdgeCreationEvent*);

        void manageTreeEdgeDeletionEvent(tree_events::TreeEdgeDeletionEvent*);

        std::shared_ptr<tree_interfaces::EdgeFactoryInterface> edge_factory;
        bool is_active;
        std::set<tree_interfaces::TreeNodeInterface*> selected_nodes;
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
