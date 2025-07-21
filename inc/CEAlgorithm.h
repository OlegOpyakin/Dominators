#include "Graph.h"

#pragma once

// Critical Edges reduction algorithm
void Graph::CEAlgorithm() {
    for(const auto& [block_id, block] : blocks_){
        if(block.successors_.size() > 1){
            for(auto succ_id: block.successors_){
                if(blocks_[succ_id].predcessors_.size() > 1){
                    // we found critical edge:
                    // from "block" to "blocks_[succ_id]"
                    // now we need to split critical edge

                    DeleteEdge(block_id, succ_id);

                    BasicBlock block;
                    blocks_.insert(std::pair(blocks_counter_,  block)); // add new block
                    auto new_block_id = blocks_counter_;
                    blocks_counter_++;

                    AddEdge(block_id, new_block_id);
                    AddEdge(new_block_id, succ_id);
                }
            }
        }
    }
}