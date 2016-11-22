//
// Created by artem on 13.11.16.
//

#ifndef MYGAME_TREEMANAGEMENT_H
#define MYGAME_TREEMANAGEMENT_H

#include "cocos2d.h"
#include "../../event_system/EventWrappers.h"
#include "TreeObjectInterfaces.h"
#include <set>

namespace tree_management {

    class TreeManager {
    public:
        static void createTreeManagers();

        static TreeManager* getActiveManager();

        static TreeManager* getPassiveManager();

        static void switchManagers();

    private:
        TreeManager();

        static TreeManager* getFirstManager();

        static TreeManager* getSecondManager();

        void set_active();

        void set_passive();

        void switchState();

        void selectNode(tree_interfaces::TreeNodeInterface*);

        void deselectNode(tree_interfaces::TreeNodeInterface*);

        void addEvents();

        void manageTreeNodeCreationEvent(tree_events::TreeNodeCreationEvent*);

        void manageTreeNodeSelectionEvent(tree_events::TreeNodeSelectionEvent*);

        void manageTreeNodeDeselectionEvent(tree_events::TreeNodeDeselectionEvent*);

        void manageTreeEdgeCreationEvent(tree_events::TreeEdgeCreationEvent*);

        void manageTreeEdgeDeletionEvent(tree_events::TreeEdgeDeletionEvent*);

        bool is_active;
        std::set<tree_interfaces::TreeNodeInterface*> selected_nodes;
    };

}


#endif //MYGAME_TREEMANAGEMENT_H
