//
// Created by artem on 27.12.16.
//

#ifndef MYGAME_CONTROLZONE_H
#define MYGAME_CONTROLZONE_H

#include "cocos2d.h"
#include "TreeEvents.h"


class ControlZone: public cocos2d::Sprite {
public:
    ControlZone(): is_active_{false}, passive_tree_selected_node{nullptr} {};

    static ControlZone* create(cocos2d::Rect control_area);

    int getScenePriority() {
        return 2;
    }

    bool isActive();

    void setActive();

    void setPassive();

    void switchState();

private:
    void manageActiveTreeNodeSelectionEvent(tree_events::TreeNodeSelectionEvent *);

    void manageActiveTreeNodeDeselectionEvent(tree_events::TreeNodeDeselectionEvent *);

    void managePassiveTreeNodeSelectionEvent(tree_events::TreeNodeSelectionEvent *);

    void managePassiveTreeNodeDeselectionEvent(tree_events::TreeNodeDeselectionEvent *);

    void addEvents();

    void initOptions();

    void addNode(cocos2d::EventMouse*, cocos2d::Scene*);

    void addForce(cocos2d::EventMouse*);

    bool is_active_;
    std::set<tree_interfaces::TreeNodeInterface*> active_tree_selected_nodes;
    tree_interfaces::TreeNodeInterface* passive_tree_selected_node;
};


#endif //MYGAME_CONTROLZONE_H
