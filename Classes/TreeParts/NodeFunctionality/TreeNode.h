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

    int getScenePriority() { return 10; };

    TreeNode();
    ~TreeNode();

    static TreeNode* create();

    score_type getBuyPrice() const;
    score_type getSellPrice() const;

    void setPhantom();
    void setReal();
    tree_interfaces::TreePart* getClone();

    int getIndex() { return index_;};
    bool isSelected() { return selected;};
    void setSelected() {selected = true; setScale(0.25);};
    void setDeselected() {selected = false; setScale(0.1);};

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


#endif //MYGAME_TreeNode_H
