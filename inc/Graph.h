#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include "BasicBlock.h"

#pragma once

class Graph{
private:
    std::map<size_t, BasicBlock> blocks_;
    size_t blocks_counter_;
public:
    Graph(): blocks_counter_(0) {};
    Graph(size_t graph_size): blocks_counter_(0) {
        for(; blocks_counter_ < graph_size; ++blocks_counter_) {
            BasicBlock block;
            blocks_.insert(std::pair(blocks_counter_,  block));
        }
    }

    void AddBlock(){
        ++blocks_counter_;
        BasicBlock block;
        blocks_.insert(std::pair(blocks_counter_,  block));
    }

    void AddEdge(size_t edge_start, size_t edge_end){
        blocks_[edge_start].AddSucc(edge_end);
        blocks_[edge_end].AddPred(edge_start);
    }

    std::map<size_t, BasicBlock> GetMap() const{
        return blocks_;
    }

    size_t GetBlocksNumber() const{
        return blocks_counter_;
    }

    void SetDominators(size_t block_id, const std::vector<size_t>& dominators){
        if(blocks_.find(block_id) != blocks_.end()){
            blocks_[block_id].dom_ = dominators;
        }
    }

    void GenerateEdges(size_t num_of_edges); // randomly generate edges
    void DAlgorithm(); // dominator search algorithm
    void DTAlgorithm(); // dominator tree algorithm
    void DFAlgorithm(); // dominance frontier algorithm
    void DumpPredecessors(const std::string& filename = "predecessors.dot", const std::string& graph_name = "PredecessorGraph"); // dump predecessors with graphvis
    void DumpDominators(const std::string& filename = "dominators.dot", const std::string& graph_name = "DominatorGraph"); // dump dominators with graphvis
    void DumpDomTree(const std::string& filename = "domtree.dot", const std::string& graph_name = "DominatorTree"); // dump dominator tree with graphvis
    void DumpDomFrontier(const std::string& filename = "domfrontier.dot", const std::string& graph_name = "DominanceFrontier"); // dump dominance frontier with graphvis
    void DumpAll(const std::string& base_name = "graph", const std::string& graph_name = "Graph"); // dump all graphs
};

void GenerateEdges(size_t num_of_edges){
}


