/*
 * We can use N nodes to store the original graph, and then use 10 nodes representing bits. For example, we 
 * would connect node 3 to a node representing bit 1 and one representing bit 2. We 1-index the original nodes
 * to make sure everything is connected to at least one bit node. We can also create 1 node that connects to
 * every non-bit node and one node that connects to just to that node. Using this, we can figure out which 
 * nodes are bit nodes by figuring out the node with degree one (sometimes the bit 512 node may have a 
 * degree of 1, but we can just check for this). In addition, we can connect bit 1 to bit 2, bit 2 to bit 4,
 * etc., and so we can figure out which bit nodes are on the boundary since they will have only 1 
 * connection. Then, the node with the lower degree is the bit 512 node. With this information, we can 
 * recover the exact order of the bit nodes and thus recover the original graph.
 */

#include "Alicelib.h"
#include <cassert>
#include <cstdio>

#include <array>
#include <numeric>
#include <vector>

using namespace std;

void Alice(int N, int M, int A[], int B[]) {
    if (N == 1) {
        InitG(1, 0);
        return;
    }

    if (N == 2) {
        if (M == 0) {
            InitG(2, M);
        } else {
            InitG(2, 1);
            MakeG(0, 0, 1);
        }
        return;
    }

    int all = 0;
    int mark = N + 1;
    vector<int> bit(10);
    iota(bit.begin(), bit.end(), N + 2);
    vector<array<int, 2>> edge;

    for (int i = 0; i < M; i++) {
        edge.push_back({A[i] + 1, B[i] + 1});
    }

    for (int i = 1; i <= N; i++) {
        edge.push_back({all, i});
        for (int j = 0; j < 10; j++) {
            if ((i >> j) & 1) {
                edge.push_back({i, bit[j]});
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        edge.push_back({N + i + 2, N + i + 3});
    }

    edge.push_back({all, mark});
    int sz = edge.size();
    InitG(N + 12, sz);

    for (int i = 0; i < sz; i++) {
        MakeG(i, edge[i][0], edge[i][1]);
    }
}

