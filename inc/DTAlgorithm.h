#include "Graph.h"

#pragma once

std::vector<size_t> Exclude(const std::vector<size_t>& vec, size_t element) {
    std::vector<size_t> result;
    for (size_t val : vec) {
        if (val != element) {
            result.push_back(val);
        }
    }
    return result;
}

size_t Head(const std::vector<size_t>& vec) {
    if (vec.empty()) {
        throw std::runtime_error("Cannot get head of empty vector");
    }
    return vec[0];
}

// return the immediate dominator
size_t Closest(const std::vector<size_t>& domset, size_t block_id, const std::map<size_t, BasicBlock>& blocks) {
    if (domset.empty()) {
        throw std::runtime_error("Cannot find closest in empty dominator set");
    }
    
    if (domset.size() == 1) {
        return domset[0];
    }
    
    size_t closest = domset[0];
    size_t max_dom_size = 0;
    
    for (size_t dom : domset) {
        auto it = blocks.find(dom);
        if (it != blocks.end()) {
            if (it->second.dom_.size() > max_dom_size) {
                max_dom_size = it->second.dom_.size();
                closest = dom;
            }
        }
    }
    
    return closest;
}

// my implementation is slightly different fro the one in .md file
// i didn't use separated check of size(Domset) == 1 , i added it into closest implementation
void Graph::DTAlgorithm() {
    DAlgorithm();
    
    for (const auto& [block_id, block] : blocks_) {
        const std::vector<size_t>& domset = block.dom_;
        std::vector<size_t> filtered_domset = Exclude(domset, block_id);

        if (filtered_domset.empty()) {
            continue;
        }

        size_t closest_dominator = Closest(filtered_domset, block_id, blocks_);
        blocks_[block_id].SetImmediateDominator(closest_dominator);
    }
}
