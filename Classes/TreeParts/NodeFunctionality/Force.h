//
// Created by artem on 27.12.16.
//

#ifndef MYGAME_FORCE_H
#define MYGAME_FORCE_H

#include "cocos2d.h"
#include "../../managers/TreeManagement/TreePartsInterfaces.h"

class Force: public tree_interfaces::ForceInterface {
public:
    Force(tree_interfaces::TreeNodeInterface* node, cocos2d::Vec2 force_vector): node_{node}, force_vector_{force_vector} {};

    static Force* create(tree_interfaces::TreeNodeInterface* node, cocos2d::Vec2 force_vector) {
        Force* force = new Force(node, force_vector);

        if (force->initWithFile(Force::kSpritePath)) {
            force->autorelease();
            force->initOptions();

            auto body = cocos2d::PhysicsBody::create(1);
            body->setDynamic(false);
            force->setPhysicsBody(body);

            return force;
        }

        CC_SAFE_DELETE(force);
        return NULL;
    }

    void submit() {
        node_->getPhysicsBody()->applyImpulse(force_vector_ * 10);  //TODO refactor to set impulce value independently
        removeFromParentAndCleanup(true);
    }

    score_type getBuyPrice() const { return 0; }

    score_type getSellPrice() const { return 0; }

private:
    void initOptions() {
        setAnchorPoint(cocos2d::Vec2(0, 0.5));
        setScale(0.1);
    };

    void update(float) {
        updatePosition();
    }

    void updatePosition() {
        setPosition(node_->getPosition());
        setRotation(-force_vector_.getAngle() * 180 / M_PI);

    }

    tree_interfaces::TreeNodeInterface* node_;
    cocos2d::Vec2 force_vector_;

    static const std::string kSpritePath;
};


#endif //MYGAME_FORCE_H
