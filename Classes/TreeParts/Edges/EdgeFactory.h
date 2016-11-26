//
// Created by yury on 26.11.16.
//

#ifndef MYGAME_EDGEFACTORY_H
#define MYGAME_EDGEFACTORY_H

#include "cocos2d.h"
#include "./managers/TreeManagement/TreeObjectInterfaces.h"
#include <vector>

using namespace tree_interfaces;

class EdgeFactory : public  EdgeFactoryInterface{
public:
    EdgeFactory();
    ~EdgeFactory();

    void setSample(TreeEdgeInterface* ) = 0;

    /**
     * Through this method you set request to create one edge
     */
    void setRequest(cocos2d::Vec2, cocos2d::Vec2) = 0;

    /**
     * Through this method you set request to create multiple edges
     */
     void setRequest(std::vector<cocos2d::Vec2>&, std::vector<cocos2d::Vec2>&) = 0;

    /**
     * This method returns the clone of sample edge
     */
    TreeEdgeInterface* getNewEdge(TreeNodeInterface*, TreeNodeInterface*) = 0;
};


#endif //MYGAME_EDGEFACTORY_H
