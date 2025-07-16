#include <iostream>
#include <vector>
#include <algorithm>

#pragma once

class BasicBlock{
public:
    std::vector<size_t> predcessors_;
    std::vector<size_t> successors_;
    std::vector<size_t> dom_;
    std::vector<size_t> dom_frontier_;
    size_t idom_; // immediate dominator
    bool has_idom_;

    BasicBlock() : idom_(0), has_idom_(false) {}

    void AddPred(size_t pred){
        predcessors_.push_back(pred);
    }

    void AddSucc(size_t succ){
        successors_.push_back(succ);
    }

    void AddDom(size_t dom){
        dom_.push_back(dom);
    }

    void AddDomFrontier(size_t dom_frontier){
        if(std::find(dom_frontier_.begin(), dom_frontier_.end(), dom_frontier) == dom_frontier_.end()){
            dom_frontier_.push_back(dom_frontier);
        }
    }
    
    void SetImmediateDominator(size_t idom) {
        idom_ = idom;
        has_idom_ = true;
    }
    
    size_t GetImmediateDominator() const {
        return idom_;
    }
    
    bool HasImmediateDominator() const {
        return has_idom_;
    }
};
