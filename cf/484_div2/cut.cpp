// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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
#define MAXN 1000000

using namespace std;

struct node {
    vector<int> connect;
    bool visited;
    int count;
};

vector<node> graph;
int ans;

void dfs(int pos) {
    graph[pos].visited = true;
    if (graph[pos].connect.size() == 1) {
        graph[pos].count = 1; 
    } else {
        for (int &i : graph[pos].connect) {
            if (!graph[i].visited) {
                graph[pos].count += graph[i].count;
            }
        }
    }

    if (graph[pos].count % 2 == 0 && pos != 0) {
        ans++;
    }
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    graph = vector<node>(n);

    for (int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        x--;
        y--;
        graph[x].connect.push_back(y);
        graph[y].connect.push_back(x);
    }

    dfs(0);

    cout << ans << '\n';

    return 0;
}
