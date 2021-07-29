// :pray: :arrayman:
// :pray: :summitosity:
// :pray: :pusheenosity:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk-duk-go:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eediosity:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinxiosity
// :pray: :eggyosity:
// :pray: :squares-are-fine:
// :pray: :see-jay:
// :pray: :stephiosity:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:
// :pray: :wayne:
// :pray: :wu:
// :pray: :vmaddur:
// :pray: :dorijanko:

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct node {
    vector<int> adj;
    bool visited;
};

int n, e;
vector<node> graph;

int main() {
    cin >> n >> e;
    graph = vector<node>(n);

    for (int i = 0; i < e; i++) {
        int a, b; cin >> a >> b;
        graph[a - 1].adj.push_back(b - 1);
        graph[b - 1].adj.push_back(a - 1);
    }

    int maxDeg = 0;
    int maxLoc = 0;

    for (int i = 0; i < n; i++) {
        if (graph[i].adj.size() > maxDeg) {
            maxDeg = graph[i].adj.size();
            maxLoc = i;
        }
    }

    //cerr << "\n\n";

    graph[maxLoc].visited = true;
    queue<pair<int, int>> q;
    for (int i : graph[maxLoc].adj) {
        q.push({i, maxLoc});
    }

    while (!q.empty()) {
        pair<int, int> top = q.front();
        q.pop();
        if (graph[top.first].visited) continue;

        cout << top.second + 1 << ' ' << top.first + 1<< '\n';
        graph[top.first].visited = true;

        for (int i : graph[top.first].adj) {
            if (!graph[i].visited) q.push({i, top.first});
        }
    }

    return 0;
}
