#include <queue>
#include <utility>
#include <vector>

#include "crocodile.h"

using namespace std;

constexpr int INF = 0x3f3f3f3f;

pair<int, int> add_d(pair<int, int> cur_d, int new_d) {
    if (new_d <= cur_d.first) {
        cur_d.second = cur_d.first;
        cur_d.first = new_d;
    } else if (new_d < cur_d.second) {
        cur_d.second = new_d;
    }

    return cur_d;
}

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
{
    vector<vector<pair<int, int>>> adj(N);
    for (int i = 0; i < M; i++) {
        adj[R[i][0]].push_back({R[i][1], L[i]});
        adj[R[i][1]].push_back({R[i][0], L[i]});
    }

    // first and second shortest distances
    vector<pair<int, int>> d(N, {INF, INF});
    vector<int> vis_count(N);

    // {second, location}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    for (int i = 0; i < K; i++) {
        int cur = P[i];
        d[cur] = {0, 0};
        pq.push({0, cur});
    }

    while (!pq.empty()) {
        auto [dd, t] = pq.top();
        pq.pop();

        if (d[t].second == dd) {
            for (auto [v, w] : adj[t]) {
                auto nxt_d = add_d(d[v], dd + w);
                if (nxt_d.second < d[v].second) {
                    pq.push({nxt_d.second, v});
                }
                d[v] = nxt_d;
            }
        }
    }

    return d[0].second;
}
