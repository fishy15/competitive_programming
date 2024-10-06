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
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    for (auto &v : a) {
        cin >> v;
    }

    // dist[v][0] = distance where we have landed
    // dist[v][1] = distance where we are moving to the side
    vector<array<int, 2>> dist(n, {INF, INF});
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;
    dist[0][0] = 0;
    pq.push({0, 0, 0});

    while (!pq.empty()) {
        auto [d, v, t]  = pq.top();
        pq.pop();

        auto process = [&](int nxt, int nxtt, int nxtd) {
            if (dist[nxt][nxtt] > nxtd) {
                dist[nxt][nxtt] = nxtd;
                pq.push({nxtd, nxt, nxtt});
            }
        };

        if (t == 0) {
            process((a[v] + v) % n, 1, d + 1);
        } else {
            process(v, 0, d);
            process((v + 1) % n, 1, d + 1);
        }
    }

    cout << dist[x][0] << '\n';

    return 0;
}
