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

void solve() {
    string s;
    cin >> s;

    int n = s.size();
    vector<array<int, 26>> psum(n + 1, array<int, 26>{});

    for (int i = 0; i < n; i++) {
        char c = s[i] - 'a';
        psum[i + 1] = psum[i];
        psum[i + 1][c]++;
    }

    auto get = [&psum](int l, int r) {
        array<int, 26> res;
        for (int i = 0; i < 26; i++) {
            res[i] = psum[r][i] - psum[l][i];
        }
        return res;
    };

    int q;
    cin >> q;

    int ans = 0;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;

        if ((r - l) % 2 != 0) {
            int m = (l + (r - 1)) / 2;

            // in the first half
            auto diff1_l = get(l, m + 1);
            auto diff1_r = get(m + 1, r);

            bool ok = true;
            bool used1 = false;
            for (int i = 0; i < 26; i++) {
                if (diff1_l[i] != diff1_r[i]) {
                    if (diff1_l[i] - diff1_r[i] == 1) {
                        ok &= !used1;
                        used1 = true;
                    } else {
                        ok = false;
                    }
                }
            }

            // in the sec half
            auto diff2_l = get(l, m);
            auto diff2_r = get(m, r);

            bool ok2 = true;
            bool used1_2 = false;
            for (int i = 0; i < 26; i++) {
                if (diff2_l[i] != diff2_r[i]) {
                    if (diff2_r[i] - diff2_l[i] == 1) {
                        ok2 &= !used1_2;
                        used1_2 = true;
                    } else {
                        ok2 = false;
                    }
                }
            }

            if (ok || ok2) {
                ans++;
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
