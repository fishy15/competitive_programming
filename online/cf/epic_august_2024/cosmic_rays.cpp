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

    vector<pair<ll, int>> segs(n);
    rep(i, 0, n) {
        cin >> segs[i].first >> segs[i].second;
    }

    vector<pair<ll, int>> st;
    for (auto [a, b] : segs) {
        ll prev_life = 0;
        while (!st.empty()) {
            if (st.back().second == b) {
                a += st.back().first - prev_life;
                st.pop_back();
            } else if (st.back().first < a) {
                prev_life = st.back().first;
                st.pop_back();
            } else {
                break;
            }
        }
        st.push_back({a, b});
        cout << st[0].first << ' ';
    }
    cout << '\n';
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
