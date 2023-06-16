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

constexpr int MAX = 300;

int x, y;
bool vis[MAX];
int dist[MAX];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> x >> y;

    queue<int> q;
    q.push(x);
    vis[x] = true;

    while (!q.empty()) {
        int t = q.front(); q.pop();

        if (t > 1 && !vis[t - 1]) {
            vis[t - 1] = true;
            dist[t - 1] = dist[t] + 1;
            q.push(t - 1);
        }

        if (3 * t < MAX && !vis[3 * t]) {
            vis[3 * t] = true;
            dist[3 * t] = dist[t] + 1;
            q.push(3 * t);
        }
    }

    cout << dist[y] << '\n';

    return 0;
}
