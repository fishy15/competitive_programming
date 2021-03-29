#include "Boblib.h"
#include <cassert>
#include <cstdio>

#include <vector>
#include <utility>
#include <array>

using namespace std;

void Bob(int V, int U, int C[], int D[]) {
    if (V == 1) {
        InitMap(1, 0);
        return;
    }

    if (V == 2) {
        if (U == 0) {
            InitMap(2, 0);
        } else {
            InitMap(2, 1);
            MakeMap(0, 1);
        }
        return;
    }

    vector<vector<int>> adj(V);
    for (int i = 0; i < U; i++) {
        adj[C[i]].push_back(D[i]);
        adj[D[i]].push_back(C[i]);
    }

    int all = -1, mark = -1;
    for (int i = 0; i < V; i++) {
        if (adj[i].size() == 1) {
            int nxt = adj[i][0];
            if ((int)(adj[nxt].size()) == V - 11) {
                all = nxt;
                mark = i;
            }
        }
    }

    vector<int> bit_num(V);
    for (int i = 0; i < V; i++) {
        if (i == all || i == mark) continue;

        bool ok = true;
        for (auto x : adj[i]) {
            if (x == all) {
                ok = false;
                break;
            }
        }

        bit_num[i] = ok;
    }

    pair<int, int> ten = {1000001, -1};
    for (int i = 0; i < V; i++) {
        if (!bit_num[i]) continue;
        int cnt = 0;
        for (int x : adj[i]) {
            if (bit_num[x]) cnt++;
        }

        if (cnt == 1) {
            ten = min(ten, {adj[i].size(), i});
        }
    }

    assert(ten.second != -1);

    int prevnum = -1;
    int cur = ten.second;
    int curp = 512;
    while (curp) {
        bit_num[cur] = curp;
        curp /= 2;

        for (int x : adj[cur]) {
            if (bit_num[x] && x != prevnum) {
                prevnum = cur;
                cur = x;
                break;
            }
        }
    }

    vector<int> correct_num(V);
    for (int i = 0; i < V; i++) {
        if (!bit_num[i] && i != all && i != mark) {
            for (int x : adj[i]) {
                correct_num[i] += bit_num[x];
            }
        }
    }

    vector<array<int, 2>> edge;
    for (int i = 0; i < U; i++) {
        int a = correct_num[C[i]];
        int b = correct_num[D[i]];
        if (a && b) {
            edge.push_back({a - 1, b - 1});
        }
    }

    InitMap(V - 12, (int)(edge.size()));
    for (auto [a, b] : edge) {
        MakeMap(a, b); 
    }
}

