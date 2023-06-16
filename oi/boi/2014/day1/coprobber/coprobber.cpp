/*
 * For every cop location, robber location, and turn, figure out who can win
 * Cop wins if cop and robber on the same location, bfs outward to find rest of cases
 * Cop wins on their turn if they can move to a location that wins immediately
 * Cop wins on robber's turn if robber has no location to move where cop loses
 * Use this information to see if there is a starting location that cop always wins at
*/

#include <cstring>
#include <array>
#include <iostream>
#include <queue>

using namespace std;

#include "coprobber.h"

int n;
int adj[MAX_N][MAX_N];
int win[MAX_N][MAX_N][2];
int par[MAX_N][MAX_N];
int deg[MAX_N][MAX_N];
int loc = -1;

void solve() {
    queue<array<int, 3>> q;

    for (int end = 0; end < n; end++) {
        q.push({end, end, 0});
        win[end][end][0] = true;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            deg[0][i] += adj[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            deg[i][j] = deg[0][j];
        }
    }

    while (!q.empty()) {
        auto [cop, rob, turn] = q.front();
        q.pop();

        // if it's cop's turn, reduce adjacent robber degrees by 1
        // else if robber's turn, mark adjacent cop moves that they can win there
        if (turn) {
            for (int i = 0; i < n; i++) {
                if (adj[i][rob] && !win[cop][i][0]) {
                    deg[cop][i]--;
                    if (!deg[cop][i]) {
                        win[cop][i][0] = true;
                        q.push({cop, i, 0});
                    }
                }
            }
        } else {
            for (int i = 0; i < n; i++) {
                if ((adj[i][cop] || i == cop) && !win[i][rob][1]) {
                    win[i][rob][1] = true;
                    par[i][rob] = cop;
                    q.push({i, rob, 1});
                }
            }
        }
    }

    for (int start = 0; start < n; start++) {
        int rob = 0;
        for (; rob < n; rob++) {
            if (!win[start][rob][1]) break;
        }

        if (rob == n) {
            loc = start;
        }
    }
}

int start(int N, bool A[MAX_N][MAX_N]) {
    n = N;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = A[i][j];
        }
    }

    solve();

    return loc;
}

int nextMove(int R) {
    loc = par[loc][R];
    return loc;
}
