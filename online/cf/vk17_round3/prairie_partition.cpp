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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    map<ll, int> cnt;
    rep(i, 0, n) {
        ll x;
        cin >> x;
        cnt[x]++;
    }

    auto check = [&](int k) {
        auto my_cnt = cnt;
        vector<ll> ends;
        rep(i, 0, k) {
            ll wanted = 1;
            while (my_cnt[wanted] > 0) {
                my_cnt[wanted]--;
                wanted *= 2;
            }

            if (wanted == 1) {
                return false;
            }
            ends.push_back(wanted / 2);
        }

        sort(all(ends));

        for (auto it = rbegin(my_cnt); it != rend(my_cnt); it++) {
            auto [v, c] = *it;
            rep(_, 0, c) {
                if (ends.empty() || 2 * ends.back() <= v) {
                    return false;
                }
                ends.pop_back();
            }
        }

        return true;
    };

    int l = 0;
    int r = cnt[1];
    int ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    if (ans == -1) {
        cout << "-1\n";
    } else {
        for (int i = ans; i <= cnt[1]; i++) {
            cout << i << ' ';
        }
        cout << '\n';
    }

    return 0;
}
