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
#define MAXN 2500

using namespace std;

int n, m;
vector<int> radj[MAXN];;
vector<tuple<int, int, ll>> edge;
ll dist[MAXN];
bool imp[MAXN];
ll ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        edge.push_back({a, b, c});
        radj[b].push_back(a);
    }

    // only mark important edge
    queue<int> q;
    q.push(n - 1);
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        if (imp[p]) continue;
        imp[p] = true;

        for (int e : radj[p]) {
            if (!imp[e]) q.push(e);
        }
    }

    for (int i = 1; i < n; i++) {
        dist[i] = -INFLL;
    }

    bool change = false;
    for (int i = 0; i < n; i++) {
        for (auto e : edge) {
            if (imp[get<0>(e)] && imp[get<1>(e)] && dist[get<0>(e)] != -INFLL) {
                if (dist[get<1>(e)] < dist[get<0>(e)] + get<2>(e)) {
                    if (i == n - 1) change = true;
                    dist[get<1>(e)] = dist[get<0>(e)] + get<2>(e);
                }
            }
        }
    }

    if (change) {
        cout << "-1\n";
    } else {
        cout << dist[n - 1] << '\n';
    }

    return 0;
}
