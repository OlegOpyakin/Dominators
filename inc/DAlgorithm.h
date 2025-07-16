#include "Graph.h"
#include <algorithm>

#pragma once

std::vector<size_t> SetAllDom(size_t size){
    std::vector<size_t> all;
    for(size_t j = 0; j < size; ++j) all.push_back(j);
    return all;
}

std::vector<size_t> Intersect(const std::vector<size_t>& vec1, const std::vector<size_t>& vec2){
    std::vector<size_t> common_data;
    std::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::back_inserter(common_data));
    return common_data;
}

void AppendToSet(std::vector<size_t>& vec, size_t element){
    if(std::find(vec.begin(), vec.end(), element) == vec.end()){
        vec.push_back(element);
        std::sort(vec.begin(), vec.end());
    }
}

bool VectorsEqual(const std::vector<size_t>& vec1, const std::vector<size_t>& vec2){
    return vec1 == vec2;
}

// create dom graph from cfg
void Graph::DAlgorithm(){
    std::map<size_t, std::vector<size_t>> Dom;
    auto blocks = blocks_;
    
    for(const auto& [block_id, block] : blocks){
        Dom[block_id] = SetAllDom(blocks_counter_);
    }
    
    if(blocks_counter_ > 0){ // block 0 is the entry block
        Dom[0] = {0};
    }
    
    bool changed = true;
    
    while(changed){
        changed = false;
        for(const auto& [block_id, block] : blocks){
            if(block_id == 0) continue; // skip entry block

            std::vector<size_t> tmp = SetAllDom(blocks_counter_);
            
            for(size_t pred_id : block.predcessors_){
                tmp = Intersect(tmp, Dom[pred_id]);
            }
            
            AppendToSet(tmp, block_id);

            if(!VectorsEqual(Dom[block_id], tmp)){
                Dom[block_id] = tmp;
                changed = true;
            }
        }
    }
    
    //Graph dom_graph(cfg.GetBlocksNumber());
    
    for(const auto& [block_id, dominators] : Dom){
        SetDominators(block_id, dominators);
    }
}
