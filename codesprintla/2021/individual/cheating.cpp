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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 2010

using namespace std;

int n;
array<int, 2> loc[MAXN];
vector<int> dist[MAXN];
bool vis[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> loc[i][0] >> loc[i][1];
    }

    for (int i = 0; i < n; i++) {
        dist[i].resize(n);
        for (int j = 0; j < n; j++) {
            dist[i][j] = abs(loc[i][0] - loc[j][0]) + abs(loc[i][1] - loc[j][1]);
        }
    }

    priority_queue<array<int, 2>, vector<array<int, 2>>, greater<>> pq;
    pq.push({0, 0});

    int ans = 0;
    while (!pq.empty()) {
        auto [d, pt] = pq.top();
        pq.pop();

        if (vis[pt]) continue;
        vis[pt] = true;
        ans += 2 * d;

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                pq.push({dist[pt][i], i});
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
