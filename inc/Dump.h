#include "Graph.h"

#pragma once

void Graph::DumpPredecessors(const std::string& filename, const std::string& graph_name){
    std::ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        std::cerr << "Error opening DOT file\n";
        return;
    }

    dotFile << "digraph " << graph_name << " {\n";
    dotFile << "    rankdir=\"TB\";\n";
    dotFile << "    node [shape=box, style=\"rounded,filled\", fillcolor=\"#e6f3ff\"];\n";
    dotFile << "    edge [color=\"#0066cc\"];\n";
    
    dotFile << "    label=\"Predecessor Tree\";\n";
    dotFile << "    labelloc=\"t\";\n";
    dotFile << "    fontsize=16;\n";
    dotFile << "    fontweight=\"bold\";\n\n";

    for (const auto& [id, block] : blocks_) {
        dotFile << "    block" << id << " [label=\"Block " << id << "\"];\n";
    }
    dotFile << "\n";

    for (const auto& [id, block] : blocks_) {
        for (size_t predId : block.predcessors_) {
            dotFile << "    block" << predId << " -> block" << id << ";\n";
        }
    }

    dotFile << "}\n";
    dotFile.close();
    std::cout << "DOT file generated: " << filename << "\n";
    system(("dot -Tpng " + filename + " -o ../plots/" + filename + ".png").c_str());
}

void Graph::DumpDominators(const std::string& filename, const std::string& graph_name){
    std::ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        std::cerr << "Error opening DOT file\n";
        return;
    }

    bool hasNonEmptyDominators = false;
    for (const auto& [id, block] : blocks_) {
        if (!block.dom_.empty()) {
            hasNonEmptyDominators = true;
            break;
        }
    }

    if (!hasNonEmptyDominators) {
        std::cout << "No dominators found, skipping dominator graph generation.\n";
        return;
    }

    dotFile << "digraph " << graph_name << " {\n";
    dotFile << "    rankdir=\"TB\";\n";
    dotFile << "    node [shape=box, style=\"rounded,filled\", fillcolor=\"#ffe6e6\"];\n";
    dotFile << "    edge [color=\"#cc0000\"];\n";
    
    dotFile << "    label=\"Dominator Tree\";\n";
    dotFile << "    labelloc=\"t\";\n";
    dotFile << "    fontsize=16;\n";
    dotFile << "    fontweight=\"bold\";\n\n";

    for (const auto& [id, block] : blocks_) {
        if (!block.dom_.empty()) {
            dotFile << "    block" << id << " [label=\"Block " << id << "\\nDom: ";
            for (size_t i = 0; i < block.dom_.size(); ++i) {
                if (i > 0) dotFile << ", ";
                dotFile << block.dom_[i];
            }
            dotFile << "\"];\n";
        }
    }
    dotFile << "\n";

    for (const auto& [id, block] : blocks_) {
        if (!block.dom_.empty()) {
            for (size_t domId : block.dom_) {
                if (domId != id) {
                    dotFile << "    block" << domId << " -> block" << id << " [style=\"dashed\"];\n";
                }
            }
        }
    }

    dotFile << "}\n";
    dotFile.close();
    std::cout << "DOT file generated: " << filename << "\n";
    system(("dot -Tpng " + filename + " -o ../plots/" + filename + ".png").c_str());
}

void Graph::DumpDomTree(const std::string& filename, const std::string& graph_name){
    std::ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        std::cerr << "Error opening DOT file\n";
        return;
    }
    
    bool hasImmediateDominators = false;
    for (const auto& [id, block] : blocks_) {
        if (block.HasImmediateDominator()) {
            hasImmediateDominators = true;
            break;
        }
    }
    
    if (!hasImmediateDominators) {
        std::cout << "No immediate dominators found, skipping dominator tree generation.\n";
        return;
    }
    
    dotFile << "digraph " << graph_name << " {\n";
    dotFile << "    rankdir=\"TB\";\n";
    dotFile << "    node [shape=box, style=\"rounded,filled\", fillcolor=\"#e6ffe6\"];\n";
    dotFile << "    edge [color=\"#009900\"];\n";
    
    dotFile << "    label=\"Dominator Tree (DT Algorithm)\";\n";
    dotFile << "    labelloc=\"t\";\n";
    dotFile << "    fontsize=16;\n";
    dotFile << "    fontweight=\"bold\";\n\n";
    
    for (const auto& [id, block] : blocks_) {
        dotFile << "    block" << id << " [label=\"Block " << id;
        if (block.HasImmediateDominator()) {
            dotFile << "\\nIDom: " << block.GetImmediateDominator();
        }
        dotFile << "\"];\n";
    }
    dotFile << "\n";
    
    for (const auto& [id, block] : blocks_) {
        if (block.HasImmediateDominator()) {
            size_t idom = block.GetImmediateDominator();
            dotFile << "    block" << idom << " -> block" << id << ";\n";
        }
    }
    
    dotFile << "}\n";
    dotFile.close();
    std::cout << "DOT file generated: " << filename << "\n";
    system(("dot -Tpng " + filename + " -o ../plots/" + filename + ".png").c_str());
}

void Graph::DumpDomFrontier(const std::string& filename, const std::string& graph_name){
    std::ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        std::cerr << "Error opening DOT file\n";
        return;
    }
    
    bool hasDominanceFrontier = false;
    for (const auto& [id, block] : blocks_) {
        if (!block.dom_frontier_.empty()) {
            hasDominanceFrontier = true;
            break;
        }
    }
    
    if (!hasDominanceFrontier) {
        std::cout << "No dominance frontiers found, skipping dominance frontier graph generation.\n";
        return;
    }
    
    dotFile << "digraph " << graph_name << " {\n";
    dotFile << "    rankdir=\"TB\";\n";
    dotFile << "    node [shape=box, style=\"rounded,filled\", fillcolor=\"#fff2e6\"];\n";
    dotFile << "    edge [color=\"#ff6600\"];\n";
    
    dotFile << "    label=\"Dominance Frontier (DF Algorithm)\";\n";
    dotFile << "    labelloc=\"t\";\n";
    dotFile << "    fontsize=16;\n";
    dotFile << "    fontweight=\"bold\";\n\n";
    
    for (const auto& [id, block] : blocks_) {
        dotFile << "    block" << id << " [label=\"Block " << id;
        if (!block.dom_frontier_.empty()) {
            dotFile << "\\nDF: ";
            for (size_t i = 0; i < block.dom_frontier_.size(); ++i) {
                if (i > 0) dotFile << ", ";
                dotFile << block.dom_frontier_[i];
            }
        }
        dotFile << "\"];\n";
    }
    dotFile << "\n";
    
    for (const auto& [id, block] : blocks_) {
        for (size_t df_block : block.dom_frontier_) {
            dotFile << "    block" << id << " -> block" << df_block << " [style=\"dashed\", label=\"DF\"];\n";
        }
    }
    
    dotFile << "}\n";
    dotFile.close();
    std::cout << "DOT file generated: " << filename << "\n";
    system(("dot -Tpng " + filename + " -o ../plots/" + filename + ".png").c_str());
}

void Graph::DumpAll(const std::string& base_name, const std::string& graph_name){
    DumpPredecessors(base_name + "_predecessors.dot", graph_name + "_Predecessors");
    DumpDominators(base_name + "_dominators.dot", graph_name + "_Dominators");
    DumpDomTree(base_name + "_domtree.dot", graph_name + "_DomTree");
    DumpDomFrontier(base_name + "_domfrontier.dot", graph_name + "_DomFrontier");
}
