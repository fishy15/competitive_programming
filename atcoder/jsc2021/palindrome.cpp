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
#define MAXN 500010

using namespace std;

struct DSU {
    int dsu[MAXN];
    int sz[MAXN];
    
    DSU() {
        iota(dsu, dsu + MAXN, 0);
        fill(sz, sz + MAXN, 1);
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
        }
    }
};

int n, k;
string s;
DSU dsu;
int cnt[MAXN][26];
int tot[MAXN];
pair<int, int> pref[MAXN][2];

int zero_l = -1;
int zero_r = -1;

bool solve(int l, int r, int k) {
    if ((l != r && k == 0) || (l == r && k == 1)) {
        zero_l = l;
        zero_r = r;
        return true;
    } else if (l >= r) {
        return false;
    } else {
        int sz = r - l + 1;
        for (int i = 0; i < sz / 2; i++) {
            dsu.join(l + i, r - i);
        }
        return solve(l, l + sz / 2 - 1, k - 1) && solve(r - sz / 2 + 1, r, k - 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> k;
    cin >> s;
    n = s.size();

    if (!solve(0, n - 1, k)) {
        cout << "impossible\n";
        return 0;
    }

    set<int> head;
    for (int i = 0; i < n; i++) {
        int x = dsu.find(i);
        cnt[x][s[i] - 'a']++;
        tot[x]++;
        head.insert(x);

        // set this for next part
        pref[i][0] = {INF, -1};
        pref[i][1] = {INF, -1};
    }

    int ans = 0;
    for (int x : head) {
        for (int i = 0; i < 26; i++) {
            int chg = tot[x] - cnt[x][i];
            if (pref[x][0].first > chg) {
                pref[x][1] = pref[x][0];
                pref[x][0] = {chg, i};
            } else if (pref[x][1].first > chg) {
                pref[x][1] = {chg, i};
            }
        }

        ans += pref[x][0].first;
    }

    int to_add = INF;
    int sz = zero_r - zero_l + 1;
    for (int i = 0; i < sz; i++) {
        int fl = dsu.find(zero_l + i);
        int fr = dsu.find(zero_r - i);

        if (zero_l + i != zero_r - i){ 
            if (pref[fl][0].second == pref[fr][0].second) {
                to_add = min(to_add, pref[fl][1].first - pref[fl][0].first);
            } else {
                to_add = 0;
            }
        }
    }

    if (zero_l != zero_r) {
        ans += to_add;
    }

    cout << ans << '\n';

    return 0;
}
