#include <random>
#include "Graph.h"
#include "DAlgorithm.h"
#include "DTAlgorithm.h"
#include "DFAlgorithm.h"
#include "Dump.h"

void TestSmallGraph() {
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
    
    std::cout << "\nTest DTAlgorithm:\n";
    cfg.DTAlgorithm();
    cfg.DumpDomTree("cfg_domtree.dot", "TestCFG_DomTree");
    
    std::cout << "\nTest DFAlgorithm:\n";
    cfg.DFAlgorithm();
    cfg.DumpDomFrontier("cfg_domfrontier.dot", "TestCFG_DomFrontier");
    
    
    std::cout << "\nTesting more complex graph:\n";
    Graph complex_cfg(4);
    complex_cfg.AddEdge(0, 1);
    complex_cfg.AddEdge(0, 2);
    complex_cfg.AddEdge(1, 3);
    complex_cfg.AddEdge(2, 3);
    
    complex_cfg.DTAlgorithm();
    complex_cfg.DumpDomTree("complex_domtree.dot", "ComplexDomTree");
    
    complex_cfg.DFAlgorithm();
    complex_cfg.DumpDomFrontier("complex_domfrontier.dot", "ComplexDomFrontier");
    
    // Print dominance frontier for complex graph
    std::cout << "\nComplex graph dominance frontiers:\n";
    for(const auto& [block_id, block] : complex_cfg.GetMap()){
        std::cout << "Block " << block_id << " DF: ";
        for(size_t df : block.dom_frontier_){
            std::cout << df << " ";
        }
        std::cout << "\n";
    }
}

void TestHardGraph1() {
    Graph graph(6);

    graph.AddEdge(0, 1);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 5);
    graph.AddEdge(2, 3);
    graph.AddEdge(3, 4);
    graph.AddEdge(4, 1);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 1);
    graph.AddEdge(6, 4);

    graph.DFAlgorithm();
    graph.DumpAll();
}

void TestHardGraph2() {
    Graph graphSBER(7);

    graphSBER.AddEdge(0, 1);
    graphSBER.AddEdge(1, 2);
    graphSBER.AddEdge(1, 3);
    graphSBER.AddEdge(3, 4);
    graphSBER.AddEdge(4, 1);
    graphSBER.AddEdge(3, 5);
    graphSBER.AddEdge(5, 6);
    graphSBER.AddEdge(6, 4);
    graphSBER.AddEdge(6, 7);
    graphSBER.AddEdge(7, 6);
    graphSBER.AddEdge(7, 4);

    graphSBER.DFAlgorithm();
    graphSBER.DumpAll();
}

/*
void TestBigGraph(size_t num_of_vars, size_t graph_size, size_t edges_number) {
    // Goal of this test is to check 
    // the convergence of the algorithm

    std::random_device r;
    std::default_random_engine e(r());
    std::uniform_int_distribution<int> dist1(0,num_of_vars-1);
    std::uniform_int_distribution<int> dist2(1,graph_size-1);
    std::uniform_int_distribution<int> dist3(1,2);

    ControlFlowGraph cfg(num_of_vars, graph_size); // cfg(num_of_vars, graph_size)

    for(int i = 0; i < edges_number; ++i){
        cfg.AddEdge(dist2(e), dist2(e)); // adding edges
    }

    for(int i = 0; i < graph_size;  ++i){
        for(int j = 0; j < num_of_vars; ++j){
            if(dist3(e) == 2)  cfg.blocks_[i].AddDef(j);
            if(dist3(e) == 2)  cfg.blocks_[i].AddKill(j);
        }
    }

    cfg.InitBitVectors();
    std::cout << "\nIterations: " << cfg.ReachingDefinitions() << "\n";
    cfg.ShowGraph();
}
*/
int main() try{
    //TestSmallGraph();
    TestHardGraph2();
}
catch (const std::exception& e){
    std::cerr << "Error: " << e.what() << "\n";
}
catch (...){
    std::cerr << "Unknown exception\n";
}
