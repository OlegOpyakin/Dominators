#include "Graph.h"

#pragma once

// calculete dominance frontier for my graph
void Graph::DFAlgorithm(){
    DTAlgorithm();

    for(auto& [block_id, block]: blocks_){
        block.dom_frontier_.clear();
    }

    for(const auto& [block_id, block]: blocks_){
        if(!block.HasImmediateDominator()){
            continue;
        }
        
        for(auto pred: block.predcessors_){
            auto tmp = pred;
            while(tmp != block.idom_){
                blocks_[tmp].AddDomFrontier(block_id);
                
                if(!blocks_[tmp].HasImmediateDominator()){ // root
                    break; 
                }
                tmp = blocks_[tmp].idom_;
            }
        }
    }
}
