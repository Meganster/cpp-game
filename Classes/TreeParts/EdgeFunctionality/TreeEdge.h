//
// Created by yury on 23.11.16.
//

#ifndef MYGAME_TREEEDGE_H
#define MYGAME_TREEEDGE_H

#include "cocos2d.h"
#include <vector>
#include <map>
#include <string>
#include "./managers/TreeManagement/TreePartsInterfaces.h"
#include "../../managers/TreeManagement/TreeEvents.h"

#include "iostream"

class TreeEdge : public tree_interfaces::TreeEdgeInterface {
public:
    TreeEdge() = delete;

    TreeEdge(tree_interfaces::TreeNodeInterface *, tree_interfaces::TreeNodeInterface *, float, float,
                 float max_force);

    int getScenePriority() { return 8; };

    static TreeEdge* create(tree_interfaces::TreeNodeInterface*, tree_interfaces::TreeNodeInterface*,
                            float, float, float);
    static TreeEdge* create(tree_interfaces::TreeNodeInterface*, tree_interfaces::TreeNodeInterface*);
    static TreeEdge* create();

    std::vector<tree_interfaces::TreeNodeInterface*> getNodes();
    void setNodes(tree_interfaces::TreeNodeInterface*, tree_interfaces::TreeNodeInterface*);

    void setPhantom();
    void setReal();
    tree_interfaces::TreeEdgeInterface* getClone(tree_interfaces::TreeNodeInterface*,
                                                 tree_interfaces::TreeNodeInterface*);
    score_type getBuyPrice() const;
    score_type getSellPrice() const;

    void setSpring(cocos2d::PhysicsJointSpring* spring) {
        spring_ = spring;
    }

    cocos2d::PhysicsJointSpring* getSpring() {
        return spring_;
    }

    void destroy();

private:
    void initOptions();
    void addEvents();
    void update(float) override;

    void removeEdge();

    float countAngle();
    float countLength();
    cocos2d::Vec2 countPosition();

    void updateEdgePosition();

    float getSpringLength();
    float getSpringForce();

    tree_interfaces::TreeNodeInterface* node_1_;
    tree_interfaces::TreeNodeInterface* node_2_;
    float stiffness_;
    float damping_;

    float init_length_;

    float max_force_;

    cocos2d::PhysicsJointSpring* spring_;

    static std::string kSpritePath;
    static constexpr float default_stiffness = 1000;
    static constexpr float default_damping = 10;
    static constexpr float default_max_force = 10000;
};


#endif //MYGAME_TREEEDGE_H
