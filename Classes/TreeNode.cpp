//
// Created by artem on 17.10.16.
//

#include "TreeNode.h"
#include <iostream>

TreeNode::TreeNode() {
    index_ = curr_max_index_++;
};

TreeNode::~TreeNode() {};

void TreeNode::initOptions() {
    setScale(0.1);
};

void TreeNode::removeTreeNode(cocos2d::EventMouse* event, TreeNode* tree_node_ptr) {
    cocos2d::Vec2 event_point = event->getLocation();
    cocos2d::Rect bounding_box = tree_node_ptr->getBoundingBox();

    if (bounding_box.containsPoint(event_point)) {
        tree_node_ptr->removeFromParentAndCleanup(true);
    }
}

void TreeNode::selectTreeNode(cocos2d::EventMouse* event, TreeNode* tree_node_ptr) {
    cocos2d::Vec2 event_point = event->getLocation();
    cocos2d::Rect bounding_box = tree_node_ptr->getBoundingBox();

    if (bounding_box.containsPoint(event_point)) {
        tree_node_ptr->setScale(0.5);
        std::cout << "Right click generated" << std::endl;

        auto select_event = TreeNodeSelectedEvent(tree_node_ptr);
        tree_node_ptr->_eventDispatcher->dispatchEvent(&select_event);
    }
}

void TreeNode::addEvents() {
    auto mouse_listener = cocos2d::EventListenerMouse::create();

    mouse_listener->onMouseDown = [this] (cocos2d::EventMouse* event) {
        if (event->getMouseButton() == MOUSE_BUTTON_LEFT) {
            this->removeTreeNode(event, this);
        } else if (event->getMouseButton() == MOUSE_BUTTON_RIGHT) {
            this->selectTreeNode(event, this);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouse_listener, this);
};

TreeNode* TreeNode::create() {
    TreeNode* node_ptr = new TreeNode();

    if (node_ptr->initWithFile(TreeNode::kSpritePath)) {
        node_ptr->autorelease();
        node_ptr->initOptions();
        node_ptr->addEvents();

        return node_ptr;
    }

    CC_SAFE_DELETE(node_ptr);
    return NULL;
}

TreeNode* TreeNode::createAttachedTreeNode(const std::vector<TreeNode*>& nodes, const cocos2d::Vec2& position) {
    TreeNode* TreeNode_ptr = TreeNode::create();
    if (TreeNode_ptr == NULL) {
        return NULL;
    } else {
        TreeNode_ptr->setPosition(position);
        return TreeNode_ptr;
    }
}

TreeNode* TreeNode::createAttachedTreeNode(const std::vector<TreeNode*>& nodes, float x, float y) {
    return TreeNode::createAttachedTreeNode(nodes, cocos2d::Vec2(x, y));
}

int TreeNode::curr_max_index_ = 0;
const std::string TreeNode::kSpritePath = "circle_blue.png";


const std::string TreeNodeSelectedEvent::kEventName = "event_selected";


