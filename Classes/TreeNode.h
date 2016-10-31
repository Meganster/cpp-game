//
// Created by artem on 17.10.16.
//

#ifndef MYGAME_TreeNode_H
#define MYGAME_TreeNode_H

#include "cocos2d.h"
#include <vector>
#include <string>

class TreeNode : public cocos2d::Sprite {
public:
    TreeNode();
    ~TreeNode();

    static TreeNode* create();
    static TreeNode* createAttachedTreeNode(const std::vector<TreeNode*>&, const cocos2d::Vec2&);
    static TreeNode* createAttachedTreeNode(const std::vector<TreeNode*>&, float, float);

    int getIndex() { return index_;};

    const static std::string kSpritePath;
private:
    void initOptions();
    void addEvents();

    static void removeTreeNode(cocos2d::EventMouse*, TreeNode*);
    static void selectTreeNode(cocos2d::EventMouse*, TreeNode*);

    static int curr_max_index_;
    int index_;
    cocos2d::Vec2 location_;
};


class TreeNodeSelectedEvent : public cocos2d::EventCustom {
public:
    TreeNodeSelectedEvent() : cocos2d::EventCustom(kEventName) {};
    TreeNodeSelectedEvent(TreeNode* tree_node_ptr) : cocos2d::EventCustom(kEventName) {
        setUserData(tree_node_ptr);
    }

    static const std::string kEventName;
};


#endif //MYGAME_TreeNode_H
