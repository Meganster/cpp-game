//
// Created by yury on 26.11.16.
//

#include "EdgeFactory.h"
#include <iostream>

EdgeFactory& EdgeFactory::getInstance() {
    static EdgeFactory instance;
    return instance;
}

EdgeFactory::EdgeFactory(): prototype_{nullptr}{}

void EdgeFactory::setPrototype(TreeEdgeInterface* edge) {
    prototype_ = edge;
}

void EdgeFactory::setRequest(TreeNodeInterface* node_1, TreeNodeInterface* node_2) {
    if (!hasRequest()) {
        start_nodes_ = std::vector<TreeNodeInterface*>{node_1};
        end_nodes_ = std::vector<TreeNodeInterface*>{node_2};
    } else {
        std::cout << "Factory is busy" << std::endl;
    }
}

void EdgeFactory::setRequest(TreeNodeInterface* end_node, std::set<TreeNodeInterface*>& start_nodes) {
    if (!hasRequest()) {
        for (auto node: start_nodes) {
            start_nodes_.push_back(node);
        }
        end_nodes_ = std::vector<TreeNodeInterface*>{end_node};
    } else {
        std::cout << "Factory is busy" << std::endl;
    }
}

score_type EdgeFactory::getBuyPrice() const {
    score_type result = 0;
    for (auto edge: getEdges()) {
        result += edge->getBuyPrice();
    }
    return result;
}

score_type EdgeFactory::getSellPrice() const {
    return 0;
}

void EdgeFactory::closeRequest() {
    start_nodes_.clear();
    end_nodes_.clear();
}

std::vector<TreeEdgeInterface*> EdgeFactory::getEdges() const {
    auto edges = std::vector<TreeEdgeInterface*>();

    for (auto start_node: start_nodes_) {
        for (auto end_node: end_nodes_) {
            edges.push_back(prototype_->getClone(start_node, end_node));
        }
    }

    return edges;
}

bool EdgeFactory::hasRequest() {
    return start_nodes_.size() != 0 || end_nodes_.size() != 0;
}