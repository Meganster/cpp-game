//
// Created by yury on 26.11.16.
//

#ifndef MYGAME_EDGEFACTORY_H
#define MYGAME_EDGEFACTORY_H

#include "cocos2d.h"
#include "./managers/TreeManagement/TreePartsInterfaces.h"
#include <vector>
#include <managers/TreeManagement/TreePartsCreation.h>

using namespace tree_part_creation;

class EdgeFactory : public  EdgeFactoryInterface{
public:
    static EdgeFactory& getInstance();

    score_type getBuyPrice() const ;

    score_type getSellPrice() const ;

    void setPrototype(TreeEdgeInterface *);

    void setRequest(TreeNodeInterface *, TreeNodeInterface *);

    void setRequest(TreeNodeInterface *, std::set<TreeNodeInterface*> &);

    std::vector<TreeEdgeInterface*> getEdges();

    void closeRequest();

private:
    EdgeFactory();

    bool hasRequest();

    std::vector<TreeNodeInterface*> start_nodes_;
    std::vector<TreeNodeInterface*> end_nodes_;
    TreeEdgeInterface* prototype_;
};


#endif //MYGAME_EDGEFACTORY_H
