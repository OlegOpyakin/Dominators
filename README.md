# Dominators

## Overview

This project implements a CFG analysis tool for computing dominators, dominance trees, and dominance frontiers. It uses several algorithms explained below for analyzing program control flow, mainly focused on the relationships between basic blocks in a graph.

## Features

- **Dominator Analysis**: Calculates dominators of each basic block.
- **Dominator Tree Construction**: Constructs the dominator tree from dominator data.
- **Dominance Frontier Calculation**: Computes the dominance frontier for each block.
- **Graph Visualization**: Generates visual representations of each computed graph.

## Algorithms Used

### Dominator Search (DAlgorithm)

-> Computes dominator sets using a fixed-point iteration algorithm.

```c++
for (auto block : F.blocks()) Dom[block] = all; 
Changed = true;

while (Changed) {
    Changed = false;
    for (auto block : blocks) {
        Set Tmp = all;
        for (auto j: preds (block)) Tmp = intersect(Tmp, Dom[j]);
        append(Tmp, block);
        Changed = Changed | (Dom[i] != Tmp);
        if(Dom[i] != Tmp) Dom[i] = Tmp;
    }
}
```

### Dominance Tree (DTAlgorithm)

-> Constructs a tree where each block's parent is its immediate dominator.

```c++
DomTree = Graph{};

for(auto [I, Domset]: Dom){
    Domset = exclude(Domset, I);
    if(empty(Domset)) continue;
    if(size(Domset) == 1){
        auto H = head(Domset);
        add(DomTree, {H, I});
        continue
    }
    auto J = closest(Domset, I);
    add(DomTree, {J, I});
}
```

### Dominance Frontier (DFAlgorithm)

-> Computes the dominance frontier for each block, which is used to identify where definitions can reach in the presence of back edges.

```c++
auto analyseDF(Function F) {
    auto IDom = F. immediateDominatorSet();
    auto DF = Map<Block, Set<Block>>{};
    for (auto B : F.blocks)
        for (auto P: F. preds (B)) {
            auto R = P;
            while (R != IDom[B]) {
                DF [R] = DF[R] join B;
                R = IDom[R];
            }
        }
    return DF;
}
```

## Build and run

```sh
mkdir build

cd build

cmake ..

make

./Dominator
```

All graphs dumps are saved in ```plots/``` by default

## Examples

Let's look at the control flow graph and apply ```DAlgorithm``` to it:

<div style="display: flex; justify-content: space-between; align-items: flex-start;">
  <img src="plots/graph_predecessors.dot.png" alt="Image 1" width="20%" />
  <img src="plots/graph_dominators.dot.png" alt="Image 2" width="70%"/>
</div>

Then let's look at thr dominator tree and dominance frontier:

<div style="display: flex; justify-content: space-between; align-items: flex-start;">
  <img src="plots/graph_domtree.dot.png" alt="Image 3" width="33%" />
  <img src="plots/graph_domfrontier.dot.png" alt="Image 4" width="40%" />
</div>