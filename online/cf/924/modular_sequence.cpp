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
#include <optional>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

// min segment length needed, last segment length used
// assumes each segment goes 0, 1, 2, ...
pair<int, int> dp[MAXN];

void precomp() {
    fill(begin(dp), end(dp), pair{INF, -1});
    dp[0] = {0, -1};

    for (int i = 0; i < MAXN; i++) {
        int moves = 0;
        int len = 1;
        while (true) {
            if (i + moves >= MAXN) break;

            ckmin(dp[i + moves], {dp[i].first+len, len});

            moves += len;
            len++;
        }
    }
}

void solve() {
    ll n, x, y, s;
    cin >> n >> x >> y >> s;

    auto orig_x = x;

    auto offset = x % y;
    s -= offset * n;
    x -= offset;

    if (s < 0 || s % y != 0) {
        cout << "NO\n";
        return;
    }

    s /= y;
    x /= y;

    // length of initial segment
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += x + i - 1;
        if (s - sum >= 0) {
            auto [moves, _] = dp[s - sum];
            if (i + moves <= n) {
                set<int> reset_locs;
                reset_locs.insert(i);
                int cur = s - sum;
                while (cur > 0) {
                    auto [idx, len] = dp[cur];
                    reset_locs.insert(i + idx);
                    auto lensum = (len - 1) * len / 2;
                    cur -= lensum;
                }

                auto cv = orig_x;
                cout << "YES\n";
                for (int j = 0; j < n; j++) {
                    if (j > 0) {
                        if (reset_locs.count(j) || j >= i + moves) {
                            cv %= y;
                        } else {
                            cv += y;
                        }
                    }
                    cout << cv << ' ';
                }
                cout << '\n';
                return;
            }
        }
    }

    cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
