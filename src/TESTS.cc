#include <random>
#include <gtest/gtest.h>
#include "DAlgorithm.h"
#include "DTAlgorithm.h"
#include "DFAlgorithm.h"
#include "CEAlgorithm.h"
#include "Dump.h"

class GraphTest : public ::testing::Test{};


TEST_F(GraphTest, TestSmallGraph) {
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

TEST_F(GraphTest, TestComplexGraph) {
    Graph complex_cfg(4);
    complex_cfg.AddEdge(0, 1);
    complex_cfg.AddEdge(0, 2);
    complex_cfg.AddEdge(1, 3);
    complex_cfg.AddEdge(2, 3);
    
    complex_cfg.DTAlgorithm();
    complex_cfg.DumpDomTree("complex_domtree.dot", "ComplexDomTree");
    
    complex_cfg.DFAlgorithm();
    complex_cfg.DumpDomFrontier("complex_domfrontier.dot", "ComplexDomFrontier");
}

TEST_F(GraphTest, TestHardGraph1) {
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

TEST_F(GraphTest, TestHardGraph2) {
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

TEST_F(GraphTest, TestGeneratedGraph) {
    Graph graph1(5); // 5 blocks, 8 edges
    graph1.GenerateEdges(8);
    graph1.DFAlgorithm();
    graph1.DumpAll("generated_small", "GeneratedSmall");
    
    Graph graph2(10); // 10 blocks, 15 edges
    graph2.GenerateEdges(15);
    graph2.DFAlgorithm();
    graph2.DumpAll("generated_large", "GeneratedLarge");
    
    Graph graph3(6); // 6 blocks, 20 edges
    graph3.GenerateEdges(20);
    graph3.DFAlgorithm();
    graph3.DumpAll("generated_dense", "GeneratedDense");
}

TEST_F(GraphTest, TestCriticalEdges) {
    Graph graphCriticalSmall(4);
    graphCriticalSmall.AddEdge(0, 1);
    graphCriticalSmall.AddEdge(2, 3);
    graphCriticalSmall.AddEdge(0, 3);
    graphCriticalSmall.DumpPredecessors("critical_small_before_CE", "CriticalSmallBeforeCE");

    graphCriticalSmall.CEAlgorithm();
    graphCriticalSmall.DumpPredecessors("critical_small_after_CE", "CriticalSmallAfterCE");

    Graph graphCriticalBig(6);
    graphCriticalBig.AddEdge(0, 1);
    graphCriticalBig.AddEdge(1, 4);
    graphCriticalBig.AddEdge(2, 3);
    graphCriticalBig.AddEdge(3, 5);
    graphCriticalBig.AddEdge(0, 3);
    graphCriticalBig.AddEdge(3, 4);

    graphCriticalBig.DumpPredecessors("critical_big_before_CE", "CriticalBigBeforeCE");

    graphCriticalBig.CEAlgorithm();
    graphCriticalBig.DumpPredecessors("critical_big_after_CE", "CriticalBigAfterCE");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}