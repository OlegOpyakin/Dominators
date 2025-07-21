#include <random>
#include "Graph.h"
#include "DAlgorithm.h"
#include "DTAlgorithm.h"
#include "DFAlgorithm.h"
#include "CEAlgorithm.h"
#include "Dump.h"

int main() try{
    // ------------------------------------------
    // tested graph:
    // bb0: x = 10;
    //      y = x + 2;
    //      goto bb1;
    // 
    // bb1: y = x + y;
    //      x = x - 1;
    //      if(x > 2) goto bb1; else goto bb2;
    //
    // bb2: t = x + y
    //      return t
    // ------------------------------------------

    Graph cfg(3); // cfg(num_of_vars, graph_size)
    cfg.AddEdge(0, 1);
    cfg.AddEdge(1, 2);
    cfg.AddEdge(1, 1);

    cfg.DumpPredecessors("cfg_predecessors.dot", "TestCFG_Predecessors");

    cfg.DAlgorithm();
    cfg.DumpDominators("cfg_dominators.dot", "TestCFG_Dominators");
    
    cfg.DTAlgorithm();
    cfg.DumpDomTree("cfg_domtree.dot", "TestCFG_DomTree");
    
    cfg.DFAlgorithm();
    cfg.DumpDomFrontier("cfg_domfrontier.dot", "TestCFG_DomFrontier");
}
catch (const std::exception& e){
    std::cerr << "Error: " << e.what() << "\n";
}
catch (...){
    std::cerr << "Unknown exception\n";
}
