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
#include <bitset>

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

    int n, m;
    cin >> n >> m;

    vector<vector<int>> knows(m);
    rep(i, 0, n) {
        string s;
        cin >> s;
        rep(j, 0, m) {
            if (s[j] == '1' && sz(knows[j]) <= m) {
                knows[j].push_back(i);
            }
        }
    }

    vector<int> total(m+1);
    vector<int> works(m+1);
    vector<bool> present(n);
    vector<bool> too_big(1 << m);
    rep(msk, 0, 1 << m) {
        int popcnt = __builtin_popcount(msk);
        basic_string<int> neighbor;
        rep(i, 0, m) {
            if (msk & (1 << i)) {
                if (too_big[msk ^ (1 << i)]) {
                    too_big[msk] = true;
                    goto end;
                }
                for (auto x : knows[i]) {
                    if (!present[x]) {
                        present[x] = true;
                        neighbor.push_back(x);
                    }
                    if (sz(neighbor) >= 20) {
                        too_big[msk] = true;
                        goto end;
                    }
                }
            }
        }

end:
        total[popcnt]++;
        if (too_big[msk] || sz(neighbor) >= popcnt) {
            works[popcnt]++;
        }

        for (auto x : neighbor) {
            present[x] = false;
        }
    }

    for (int i = 0; i < m; i++) {
        if (total[i+1] != works[i+1]) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << m << '\n';

    return 0;
}
