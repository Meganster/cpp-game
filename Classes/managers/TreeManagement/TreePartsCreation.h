//
// Created by artem on 11/26/16.
//

#ifndef MYGAME_TREEPARTSCREATION_H
#define MYGAME_TREEPARTSCREATION_H

#include "TreePartsInterfaces.h"

using namespace tree_interfaces;

namespace tree_part_creation {
    class EdgeFactoryInterface: public Scorable {
    public:
        /**
         * Through this method you set edge sample to factory
         */
        virtual void setPrototype(TreeEdgeInterface *) = 0;

        /**
         * Through this method you set request to create one edge
         */
        virtual void setRequest(TreeNodeInterface *, TreeNodeInterface *) = 0;

        /**
         * Through this method you set request to create multiple edges
         */
        virtual void setRequest(TreeNodeInterface *, std::set<TreeNodeInterface *> &) = 0;

        /**
         * This method returns the clone of sample edge
         */
        virtual std::vector<TreeEdgeInterface*> getEdges() const = 0;

        /**
         * This method flushes all inner request structures
         */
        virtual void closeRequest() = 0;
    };
}

#endif //MYGAME_TREEPARTSCREATION_H
