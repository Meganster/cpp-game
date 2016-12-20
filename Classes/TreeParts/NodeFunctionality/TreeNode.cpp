//
// Created by artem on 17.10.16.
//

#include "TreeNode.h"
#include "./managers/TreeManagement/TreeEvents.h"
#include <iostream>

TreeNode::TreeNode() {
    index_ = curr_max_index_++;
    selected = false;
    isAdding = false;
    isSelecting = false;
};

TreeNode::~TreeNode() {};

void TreeNode::initOptions() {
    setScale(0.1);
};

void TreeNode::rectScale(cocos2d::Rect* bound, int scale) {
    bound->setRect(bound->getMinX(), bound->getMinY(), scale * bound->getMaxX(), scale * bound->getMaxY());
    //std::cout << bound->getMaxX() << " " << bound->getMaxY() << std::endl;
}

void TreeNode::removeTreeNode(cocos2d::EventMouse* event, TreeNode* tree_node_ptr) {
    cocos2d::Vec2 event_point = event->getLocationInView();
    cocos2d::Rect bounding_box = tree_node_ptr->getBoundingBox();

    if (bounding_box.containsPoint(event_point)) {
        tree_node_ptr->removeFromParentAndCleanup(true);
    }
}

void TreeNode::addForce(cocos2d::EventMouse* event, TreeNode* tree_node_ptr) {
    cocos2d::Vec2 event_point = event->getLocationInView();
    cocos2d::Rect bounding_box = tree_node_ptr->getBoundingBox();
    //rectScale(&bounding_box, 2);

    if (bounding_box.containsPoint(event_point)) {
        std::cout << event->getCursorX() << " " << event->getCursorY() << std::endl;
    }
}

void TreeNode::addTreeNode(cocos2d::EventMouse* event, TreeNode* tree_node_ptr) {
    isAdding = false;
    cocos2d::Vec2 event_point = event->getLocationInView();
    std::cout << event_point.x << "\t" << event_point.y << std::endl;

    auto new_node = TreeNode::create();
    new_node->setPosition(event_point);
    auto e = tree_events::TreeNodeCreationEvent(new_node, tree_node_ptr->getScene());
    tree_node_ptr->_eventDispatcher->dispatchEvent(&e);

}

void TreeNode::selectTreeNode(cocos2d::EventMouse* event, TreeNode* tree_node_ptr) {
    cocos2d::Vec2 event_point = event->getLocationInView();
    cocos2d::Rect bounding_box = tree_node_ptr->getBoundingBox();

    if (bounding_box.containsPoint(event_point)) {

        if (tree_node_ptr->isSelected()) {
            tree_node_ptr -> selected = false;
            auto event = tree_events::TreeNodeDeselectionEvent(tree_node_ptr);
            tree_node_ptr->_eventDispatcher->dispatchEvent(&event);
        } else {
            tree_node_ptr -> selected = true;
            auto event = tree_events::TreeNodeSelectionEvent(tree_node_ptr);
            tree_node_ptr->_eventDispatcher->dispatchEvent(&event);
        }

        event->stopPropagation();
    }
}

void TreeNode::addEvents() {
    auto mouse_listener = cocos2d::EventListenerMouse::create();

    mouse_listener->onMouseUp = [this] (cocos2d::EventMouse* event) {
        if (event->getMouseButton() == MOUSE_BUTTON_MIDDLE) {
            this->addForce(event, this);
        }
    };

    mouse_listener->onMouseDown = [this] (cocos2d::EventMouse* event) {
        if (event->getMouseButton() == MOUSE_BUTTON_RIGHT) {
            //this->removeTreeNode(event, this);
        } else if( event->getMouseButton() == MOUSE_BUTTON_LEFT) {
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

        auto body = cocos2d::PhysicsBody::create(1);    // TODO Refactor (just a test)
        node_ptr->setPhysicsBody(body);

        return node_ptr;
    }

    CC_SAFE_DELETE(node_ptr);
    return NULL;
}

score_type TreeNode::getBuyPrice() const {
    return 0;
}

score_type TreeNode::getSellPrice() const {
    return 0;
}

void TreeNode::setPhantom() {}

void TreeNode::setReal() {}


int TreeNode::curr_max_index_ = 0;
bool TreeNode::isAdding = false;
bool TreeNode::isSelecting = false;
const std::string TreeNode::kSpritePath = "circle_blue.png";

