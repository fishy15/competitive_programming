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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> ppl(n);
    for (auto &[a, b] : ppl) {
        cin >> a >> b;
    }

    sort(all(ppl));

    priority_queue<int, vector<int>, greater<>> pq;
    ll cost = 0;
    int taken = 0;
    for (int i = n-1; i >= 0; i--) {
        pq.push(ppl[i].second);
        if (i + taken < ppl[i].first) {
            cost += pq.top();
            pq.pop();
            taken++;
        }
    }

    cout << cost << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
