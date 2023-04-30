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

int n;
ll ans;

template<typename T>
T ckmin(T &a, T b) {
    return a = min(a, b);
}

void solve(char c, const string &b) {
    int sz = b.size();
    vector<array<int, 26>> cur(sz, array<int, 26>{});

    for (int i = 0; i < sz; i++) {
        cur[i].fill(1);
        cur[i][b[i] - 'a'] = 0;
    }

    while (sz > 0) {
        vector<array<int, 26>> nxt(sz / 2, array<int, 26>{});

        for (int v = 0; v < sz / 2; v++) {
            nxt[v].fill(INF);

            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    ckmin(nxt[v][i], cur[v][j] + cur[v + sz / 2][j] + (i != j));
                }
            }
        }

        cur = nxt;
        sz /= 2;
    }

    auto &ans = cur[0];
    for (int i = 0; i < 26; i++) {
        if (c - 'a' != i) {
            ans[i]++;
        }
    }

    ::ans += *min_element(ans.begin(), ans.end());
}

void solve(const string &a, const string &b) {
    int sz1 = a.size();
    int sz2 = b.size();

    int diff = 0;
    while ((1 << diff) < sz2 / sz1) diff++;

    vector<string> comp(sz1);
    for (int i = 0; i < sz2; i++) {
        comp[i % sz1] += b[i];
    }

    for (int i = 0; i < sz1; i++) {
        solve(a[i], comp[i]);
    }

    ans += diff;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    string prev = "";
    for (int i = 0; i < n; i++) {
        string s; cin >> s;

        if (i > 0) {
            solve(prev, s);
        }

        prev = s;
    }

    cout << ans << '\n';

    return 0;
}
