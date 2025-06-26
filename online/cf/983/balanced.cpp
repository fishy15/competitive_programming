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
#include <cassert>

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

bool check(vector<ll> a, const vector<ll> &ops) {
    int n = sz(a);
    rep(i, 0, n) {
        if (ops[i] < 0) {
            return false;
        }

        a[(i - 1 + n) % n] += ops[i];
        a[i] += 2 * ops[i];
        a[(i + 1) % n] += ops[i];
    }

    rep(i, 0, n) {
        if (a[0] != a[i]) {
            return false;
        }
    }
    return true;
}

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    vector<ll> diff(n);
    rep(i, 0, n) {
        diff[i] = a[(i+1)%n] - a[i];
    }

    auto conv = [&](int x) {
        int pos = x / 2;
        if (x % 2 == 1) {
            pos += n / 2 + 1;
        }
        return pos;
    };

    // moves for 0, 2, 4, ..
    vector<ll> moves_diff(n+1);
    // moves from i to i-2
    auto move_back = [&](int i, ll x) {
        int start = conv((i + 1) % n);
        int end = start + n/2;
        if (end <= n) {
            moves_diff[start] += x;
            moves_diff[end] -= x;
        } else {
            moves_diff[start] += x;
            moves_diff[n] -= x;
            moves_diff[0] += x;;
            moves_diff[end % n] -= x;
        }
    };

    int cur = 0;
    rep(i, 0, n) {
        move_back(cur, -diff[cur]);
        int nxt = (cur - 2 + n) % n;
        diff[nxt] += diff[cur];
        diff[cur] = 0;
        cur = nxt;
    }

    vector<ll> moves(n);
    moves[0] = moves_diff[0];
    rep(i, 1, n) {
        moves[i] = moves[i-1] + moves_diff[i];
    }

    auto mini = *min_element(all(moves));
    ll to_add = 0;
    if (mini < 0) {
        to_add = -mini;
    }

    vector<ll> ans(n);
    rep(i, 0, n) {
        ans[i] = moves[conv(i)] + to_add;
    }

    assert(check(a, ans));
    rep(i, 0, n) {
        cout << ans[i] << ' ';
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
