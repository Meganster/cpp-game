//
// Created by artem on 17.10.16.
//

#ifndef MYGAME_TreeNode_H
#define MYGAME_TreeNode_H

#include "cocos2d.h"
#include <vector>
#include <string>
#include "event_system/EventWrappers.h"
#include "./managers/TreeManagement/TreePartsInterfaces.h"

class TreeNode : public tree_interfaces::TreeNodeInterface {
public:
    TreeNode();
    ~TreeNode();

    static TreeNode* create();
    static TreeNode* createAttachedTreeNode(const std::vector<TreeNode*>&, const cocos2d::Vec2&);

    score_type getBuyPrice() const;
    score_type getSellPrice() const;

    void setPhantom();
    void setReal();
    tree_interfaces::TreePart* getClone();

    int getIndex() { return index_;};
    bool isSelected() { return selected;};

    const static std::string kSpritePath;
private:
    void initOptions();
    void addEvents();

    static void removeTreeNode(cocos2d::EventMouse*, TreeNode*);
    static void selectTreeNode(cocos2d::EventMouse*, TreeNode*);
    static void addTreeNode(cocos2d::EventMouse*, TreeNode*);
    static void addForce(cocos2d::EventMouse*, TreeNode*);
    static void rectScale(cocos2d::Rect*, int);

    static int curr_max_index_;
    int index_;
    bool selected;
    static bool isAdding;
    static bool isSelecting;
    cocos2d::Vec2 location_;
};


class TreeNodeSelectedEvent : public event_wrappers::MyEventCustom {
public:
    //TreeNodeSelectedEvent() : event_wrappers::MyEventCustom(kEventName) {};
    TreeNodeSelectedEvent() : event_wrappers::MyEventCustom(this) {};
    TreeNodeSelectedEvent(int val) : event_wrappers::MyEventCustom(this), someVar(val) {};

    static const std::string kEventName;

    int someVar;

};


#endif //MYGAME_TreeNode_H
