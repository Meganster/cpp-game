//
// Created by yury on 26.11.16.
//

#ifndef MYGAME_EDGEFACTORY_H
#define MYGAME_EDGEFACTORY_H

#include "cocos2d.h"
#include "./managers/TreeManagement/TreePartsInterfaces.h"
#include "./managers/TreeManagement/TreePartsCreation.h"
#include "./TreeEdge.h"
#include <vector>

using namespace tree_part_creation;

class EdgeFactory : public  EdgeFactoryInterface{
public:
    EdgeFactory();
    ~EdgeFactory();

    /**
     * Through this method you set edge sample to factory
     */
     void setPrototype(TreeEdge* edge_for_prototype);

    /**
     * Through this method you set request to create one edge
     */
     void setRequest(cocos2d::Vec2 coordinate_of_begin, cocos2d::Vec2 coordinate_of_end);

    /**
     * Through this method you set request to create multiple edges
     */
     void setRequest(cocos2d::Vec2 coordinate_of_begin, std::vector<cocos2d::Vec2>& coordinates_of_end);

    /**
     * This method returns the clone of sample edge
     */
     std::vector<TreeEdge*> getEdges();

    /**
     * This method flushes all inner request structures
     */
     void closeRequest();

private:
    TreeEdge* prototype_of_edge;
};


#endif //MYGAME_EDGEFACTORY_H
