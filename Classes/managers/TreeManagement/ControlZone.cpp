//
// Created by artem on 27.12.16.
//

#include "ControlZone.h"
#include <iostream>
#include "../../TreeParts/NodeFunctionality/TreeNode.h"     // due to this and following inclusions
                                                            // ControlZone has been moved to the separate file
#include "../../TreeParts/EdgeFunctionality/TreeEdge.h"
#include "../../TreeParts/EdgeFunctionality/EdgeFactory.h"
#include "../../TreeParts/NodeFunctionality/Force.h"

ControlZone* ControlZone::create(cocos2d::Rect control_area) {
    auto control_zone = new ControlZone();

    control_zone->autorelease();
    control_zone->initOptions();
    control_zone->addEvents();

    control_zone->setPosition(control_area.getMinX(), control_area.getMinY());
    control_zone->setContentSize(cocos2d::Size(
            control_area.getMaxX() - control_area.getMinX(),
            control_area.getMaxY() - control_area.getMinY()
    ));

    return control_zone;
}

bool ControlZone::isActive() {
    return is_active_;
}

void ControlZone::setActive() {
    is_active_ = true;
}

void ControlZone::setPassive() {
    if (is_active_) {
        is_active_ = false;

        for (auto node: active_tree_selected_nodes) {
            node->setDeselected();
        }
        active_tree_selected_nodes.clear();

        if (passive_tree_selected_node != nullptr) {
            passive_tree_selected_node->setDeselected();
            passive_tree_selected_node = nullptr;
        }
    }
}

void ControlZone::switchState() {
    if (isActive()) {
        setPassive();
    } else {
        setActive();
    }
}

void ControlZone::manageActiveTreeNodeSelectionEvent(tree_events::TreeNodeSelectionEvent *event) {
    event->selected_node->setSelected();
    active_tree_selected_nodes.insert(event->selected_node);

    std::cout << "Control zone: active tree node selected" << std::endl;
    std::cout << "Total selected " << active_tree_selected_nodes.size() << std::endl << std::endl;
}

void ControlZone::manageActiveTreeNodeDeselectionEvent(tree_events::TreeNodeDeselectionEvent *event) {
    if (active_tree_selected_nodes.count(event->deselected_node)) {
        event->deselected_node->setDeselected();
        active_tree_selected_nodes.erase(event->deselected_node);
    }

    std::cout << "Control zone: active tree node deselected" << std::endl;
    std::cout << "Total selected " << active_tree_selected_nodes.size() << std::endl << std::endl;
}

void ControlZone::managePassiveTreeNodeSelectionEvent(tree_events::TreeNodeSelectionEvent *event) {
    event->selected_node->setSelected();
    if (passive_tree_selected_node != nullptr) {
        passive_tree_selected_node->setDeselected();
    }
    passive_tree_selected_node = event->selected_node;

    std::cout << "Control zone: passive tree node selected" << std::endl;
}

void ControlZone::managePassiveTreeNodeDeselectionEvent(tree_events::TreeNodeDeselectionEvent* event) {
    if (passive_tree_selected_node != nullptr && passive_tree_selected_node == event->deselected_node) {
        passive_tree_selected_node->setDeselected();
        passive_tree_selected_node = nullptr;
    }

    std::cout << "Control zone: passive tree node deselected" << std::endl;
}

void ControlZone::addNode(cocos2d::EventMouse *event, cocos2d::Scene *scene) {
    auto new_node = TreeNode::create();
    new_node->setPosition(event->getLocationInView());

    auto factory = EdgeFactory::getInstance();
    factory.setPrototype(TreeEdge::create());

    auto e = tree_events::TreeNodeCreationEvent(new_node, active_tree_selected_nodes, scene, &factory);
    active_tree_selected_nodes.clear();

    _eventDispatcher->dispatchEvent(&e);
}

void ControlZone::addForce(cocos2d::EventMouse *event) {
    if (passive_tree_selected_node != nullptr) {
        auto force = Force::create(passive_tree_selected_node,
                                   event->getLocationInView() - passive_tree_selected_node->getPosition());

        auto e = tree_events::ForceApplyingEvent(passive_tree_selected_node, force);
        passive_tree_selected_node->setDeselected();
        passive_tree_selected_node = nullptr;

        _eventDispatcher->dispatchEvent(&e);
    }
}

void ControlZone::addEvents() {
    auto select_node_call_back = [this](tree_events::TreeNodeSelectionEvent* event) -> void {
        if (getBoundingBox().containsPoint(event->selected_node->getPosition())) {
            if (isActive()) {
                manageActiveTreeNodeSelectionEvent(event);
            } else {
                managePassiveTreeNodeSelectionEvent(event);
            }
        }
    };
    auto select_node_listener = event_wrappers::create_listener<tree_events::TreeNodeSelectionEvent>(select_node_call_back);
    _eventDispatcher->addEventListenerWithFixedPriority(select_node_listener, 1);

    auto deselect_node_call_back = [this](tree_events::TreeNodeDeselectionEvent* event) -> void {
        if (getBoundingBox().containsPoint(event->deselected_node->getPosition())) {
            if (isActive()) {
                manageActiveTreeNodeDeselectionEvent(event);
            } else {
                managePassiveTreeNodeDeselectionEvent(event);
            }
        }
    };
    auto deselect_node_listener = event_wrappers::create_listener<tree_events::TreeNodeDeselectionEvent>(deselect_node_call_back);
    _eventDispatcher->addEventListenerWithFixedPriority(deselect_node_listener, 1);


    auto mouse_listener = cocos2d::EventListenerMouse::create();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouse_listener, this);
    mouse_listener->onMouseDown = [this] (cocos2d::EventMouse* event) {
        if (getBoundingBox().containsPoint(event->getLocationInView())) {
            if (isActive()) {
                if (event->getMouseButton() == MOUSE_BUTTON_LEFT) {
                    this->addNode(event, getScene());
                };
            } else {
                if (event->getMouseButton() == MOUSE_BUTTON_LEFT) {
                    this->addForce(event);
                }
            }
        }
    };

}

void ControlZone::initOptions() {

}
