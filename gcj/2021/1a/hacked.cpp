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
    int n, q; cin >> n >> q;
    vector<pair<string, int>> ppl(n);

    for (int i = 0; i < n; i++) {
        cin >> ppl[i].first >> ppl[i].second;
    }

    array<ll, 70000> beg, end;
    beg.fill(0);
    end.fill(0);
    int m = q / 2;

    vector<int> beg_mask(1 << m);
    vector<int> end_mask(1 << (q - m));
    for (int i = 0; i < (1 << m); i++) {
        vector<int> res(n);
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if ((ppl[j].first[k] == 'T') == ((i >> k) & 1)) {
                    res[j]++;
                }
            }
        }

        bool works = true;
        for (int j = 0; j < n; j++) {
            if (res[j] > ppl[j].second) {
                works = false;
                break;
            } else {
                res[j] = ppl[j].second - res[j];
            }
        }

        if (works) {
            int idx = 0;
            int mul = 1;
            for (int j = 0; j < n; j++) {
                idx += mul * res[j];
                mul *= 41;
            }
            beg[idx]++;
            beg_mask[i] = idx;
        } else {
            beg_mask[i] = -1;
        }
    }

    for (int i = 0; i < (1 << (q - m)); i++) {
        vector<int> res(n);
        for (int j = 0; j < n; j++) {
            for (int k = m; k < q; k++) {
                if ((ppl[j].first[k] == 'T') == ((i >> (k - m)) & 1)) {
                    res[j]++;
                }
            }
        }

        bool works = true;
        for (int j = 0; j < n; j++) {
            if (res[j] > ppl[j].second) {
                works = false;
                break;
            }
        }

        if (works) {
            int idx = 0;
            int mul = 1;
            for (int j = 0; j < n; j++) {
                idx += mul * res[j];
                mul *= 41;
            }
            end[idx]++;
            end_mask[i] = idx;
        } else {
            end_mask[i] = -1;
        }
    }

    vector<array<ll, 2>> num(q);
    ll tot = 0;
    for (int i = 0; i < (1 << m); i++) {
        if (beg_mask[i] != -1) {
            ll combo = end[beg_mask[i]];
            tot += combo;
            for (int j = 0; j < m; j++) {
                num[j][(i >> j) & 1] += combo;
            }
        }
    }

    for (int i = 0; i < (1 << (q - m)); i++) {
        if (end_mask[i] != -1) {
            ll combo = beg[end_mask[i]];
            for (int j = m; j < q; j++) {
                num[j][(i >> (j - m)) & 1] += combo;
            }
        }
    }

    ll numer = 0;
    string ans = "";
    for (int i = 0; i < q; i++) {
        if (num[i][0] > num[i][1]) {
            numer += num[i][0];
            ans += 'F';
        } else {
            numer += num[i][1];
            ans += 'T';
        }
    }

    ll g = gcd(numer, tot);
    numer /= g;
    tot /= g;

    cout << ans << ' ' << numer << '/' << tot << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
