// :pray: :steph:
// :pray: :bakekaga:

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
#define MAXN 1000000

using namespace std;

int n, m, r, k;

ll prob(int x, int y) {
    ll l = max(1, x - r + 1);
    ll rr = min(n, x + r - 1) - r + 1;
    ll u = max(1, y - r + 1);
    ll d = min(m, y + r - 1) - r + 1;
    return (rr - l + 1) * (d - u + 1);
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> m >> r >> k;
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, less<array<ll, 3>>> pq;
    array<ll, 3> init = {prob(n / 2 + 1, m / 2 + 1), n / 2 + 1, m / 2 + 1};
    pq.push(init);

    int count = 0;
    ll ans = 0;
    set<array<ll, 2>> vis;

    while (count < k) {
        array<ll, 3> t = pq.top();
        pq.pop();
        if (vis.count({t[1], t[2]})) {
            continue;
        }
        /* cout << t[0] << ' ' << t[1] << ' ' << t[2] << '\n'; */
        count++;
        ans += t[0];
        vis.insert({t[1], t[2]});

        if (t[1] > 1) {
            if (!vis.count({t[1] - 1, t[2]})) {
                pq.push({prob(t[1] - 1, t[2]), t[1] - 1, t[2]});
            }
        }

        if (t[1] < n) {
            if (!vis.count({t[1] + 1, t[2]})) {
                pq.push({prob(t[1] + 1, t[2]), t[1] + 1, t[2]});
            }
        }

        if (t[2] > 1) {
            if (!vis.count({t[1], t[2] - 1})) {
                pq.push({prob(t[1], t[2] - 1), t[1], t[2] - 1});
            }
        }

        if (t[2] < m) {
            if (!vis.count({t[1], t[2] + 1})) {
                pq.push({prob(t[1], t[2] + 1), t[1], t[2] + 1});
            }
        }
    }
    
    cout << setprecision(10) << 1.0 * ans / (n - r + 1) / (m - r + 1) << '\n';
    return 0;
}
