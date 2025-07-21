#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <random>
#include <algorithm>
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

    void DeleteEdge(size_t edge_start, size_t edge_end){
        blocks_[edge_start].DeleteSucc(edge_end);
        blocks_[edge_end].DeletePred(edge_start);
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
    void CEAlgorithm(); // reduce all critical edges
    void DumpPredecessors(const std::string& filename = "predecessors.dot", const std::string& graph_name = "PredecessorGraph"); // dump predecessors with graphvis
    void DumpDominators(const std::string& filename = "dominators.dot", const std::string& graph_name = "DominatorGraph"); // dump dominators with graphvis
    void DumpDomTree(const std::string& filename = "domtree.dot", const std::string& graph_name = "DominatorTree"); // dump dominator tree with graphvis
    void DumpDomFrontier(const std::string& filename = "domfrontier.dot", const std::string& graph_name = "DominanceFrontier"); // dump dominance frontier with graphvis
    void DumpAll(const std::string& base_name = "graph", const std::string& graph_name = "Graph"); // dump all graphs
};

void Graph::GenerateEdges(size_t num_of_edges){
    if (blocks_counter_ == 0) {
        throw std::runtime_error("Error: Cannot generate edges for empty graph\n");
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> block_dist(0, blocks_counter_ - 1);
    
    for (auto& [id, block] : blocks_) {
        block.predcessors_.clear();
        block.successors_.clear();
    }
    
    for (size_t i = 0; i < blocks_counter_ - 1; ++i) {
        size_t target = i + 1;
        AddEdge(i, target);
        num_of_edges--;
    }
    
    size_t attempts = 0;
    const size_t max_attempts = num_of_edges * 10;
    
    while (num_of_edges > 0 && attempts < max_attempts) {
        size_t from = block_dist(gen);
        size_t to = block_dist(gen);
        
        if (from == to && gen() % 3 == 0) {
            attempts++;
            continue;
        }
        
        bool edge_exists = false;
        for (size_t succ : blocks_[from].successors_) {
            if (succ == to) {
                edge_exists = true;
                break;
            }
        }
        
        if (!edge_exists) {
            AddEdge(from, to);
            num_of_edges--;
        }
        
        attempts++;
    }
    
    blocks_[0].predcessors_.clear();
    
    for (auto& [id, block] : blocks_) {
        if (id != 0) {
            block.successors_.erase(
                std::remove(block.successors_.begin(), block.successors_.end(), 0),
                block.successors_.end()
            );
        }
    }
}


