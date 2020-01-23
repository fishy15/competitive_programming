#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1001

using namespace std;

struct node {
    int parent;
    set<int> child;
    bool visited;
};

int n, m;
string grid[MAXN];
// graph[row][color]
node* graph[MAXN][MAXN];
int color[MAXN][MAXN];

ll calc(int i, int c) {
    /* cout << '\t' << i << ' ' << c << '\n'; */ if (graph[i][c]->visited) {
        return 1LL;
    }

    node* n = graph[i][c];
    n->visited = true;

    ll ans = 1;
    for (int c2 : n->child) {
        ans *= calc(i + 1, c2);
        ans %= MOD;
    }

    ans++;
    ans %= MOD;
    return ans;
}

int main() {
    ifstream fin("cave.in");
    ofstream fout("cave.out");

    fin >> n >> m;
    for (int i = 0; i < n; i++) {
        fin >> grid[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        int cnt = 1;
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                if (grid[i][j - 1] == '.') {
                    color[i][j] = color[i][j - 1];
                } else {
                    color[i][j] = cnt++;
                    graph[i][color[i][j]] = new node;
                }

                if (grid[i + 1][j] == '.') {
                    if (graph[i + 1][color[i + 1][j]]->parent == 0) {
                        graph[i + 1][color[i + 1][j]]->parent = color[i][j];
                        graph[i][color[i][j]]->child.insert(color[i + 1][j]);
                    } else if (graph[i + 1][color[i + 1][j]]->parent != color[i][j]) {
                        for (int c : graph[i][color[i][j]]->child) {
                            graph[i][graph[i + 1][color[i + 1][j]]->parent]->child.insert(c);
                        }
                        graph[i][color[i][j]] = graph[i][graph[i + 1][color[i + 1][j]]->parent];
                    }
                }
            }
        }
    }

    /* for (int i = 0; i < n; i++) { */
    /*     for (int j = 0; j < m; j++) { */
    /*         cout << color[i][j] << ' '; */
    /*     } */
    /*     cout << '\n'; */
    /* } */

    ll ans = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                ans *= calc(i, color[i][j]);
                ans %= MOD;
            }
        }
    }

    fout << ans << '\n';

    return 0;
}

