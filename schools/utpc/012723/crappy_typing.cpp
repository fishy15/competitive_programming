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

    int n, d;
    cin >> n >> d;

    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    auto check = [&](int m) {
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        for (int i = 0; i < m; i++) {
            pq.push(0);
        }

        ll ans = 0;
        for (auto x : t) {
            auto cur = pq.top();
            pq.pop();

            cur += x;
            ans = max(ans, cur);
            pq.push(cur);
        }

        return ans <= d;
    };

    int l = 1;
    int r = n;
    int ans = -1;

    while (l <= r) {
        int m = l + (r - l) / 2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}
