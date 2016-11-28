//
// Created by yury on 26.11.16.
//

#include "EdgeFactory.h"

EdgeFactory::EdgeFactory(){
    prototype_of_edge = NULL;
};

EdgeFactory::~EdgeFactory(){
   delete prototype_of_edge;
};

void EdgeFactory::setPrototype(TreeEdge* edge_for_prototype){
    prototype_of_edge = edge_for_prototype->getClone();
}

/**
 * Through this method you set request to create one edge
 */
void EdgeFactory::setRequest(cocos2d::Vec2 coordinate_of_begin, cocos2d::Vec2 coordinate_of_end){
    TreeEdge* newEdge = new TreeEdge(coordinate_of_begin, coordinate_of_end);
}

/**
 * Through this method you set request to create multiple edges
 */
void EdgeFactory::setRequest(cocos2d::Vec2 coordinate_of_begin, std::vector<cocos2d::Vec2>& coordinates_of_end){
    //mainly similar to first setRequest
}

/**
 * This method returns the clone of sample edge
 */
std::vector<TreeEdge*> EdgeFactory::getEdges(){
    return prototype_of_edge->getClone();
}

/**
 * This method flushes all inner request structures
 */
void EdgeFactory::closeRequest(){
    //close allRequest
}
