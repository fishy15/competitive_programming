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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 5010

using namespace std;

int n, m;
int tasty[MAXN];
pair<int, int> cows[MAXN];
vector<int> cow_fav[MAXN];
int max_cow;
ll tot = 2;

ll modpow(ll n, int e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * n % MOD;
        n = n * n % MOD;
        e >>= 1;
    }
    return res;
}

int get_cnt(int lim, vector<int> &favs) {
    int l = 0;
    int r = (int)(favs.size()) - 1;
    int ans = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (favs[m] <= lim) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return ans + 1;
}

void solve(int cow, bool rev) {
    vector<int> cur;
    for (int i = 0; i < n; i++) {
        if (rev) {
            cur.push_back(tasty[n - i - 1]);
        } else {
            cur.push_back(tasty[i]);
        }
    }

    int pos;
    int eaten = 0;
    for (pos = 0; pos < n; pos++) {
        if (cur[pos] == cows[cow].first) {
            eaten++;
            cur[pos] = 0;
        }
        if (eaten == cows[cow].second) break;
    }

    if (eaten != cows[cow].second) return;

    vector<int> l_cnt(n + 1);
    vector<int> r_cnt(n + 1);
    for (int i = 0; i < pos; i++) {
        if (cur[i]) l_cnt[cur[i]]++;
    }
    for (int i = pos + 1; i < n; i++) {
        if (cur[i]) r_cnt[cur[i]]++;
    }

    // solve for placing in either location
    int tot_ans = 1;
    ll tot_combo = 1;
    for (int i = 1; i <= n; i++) {
        int cnt1 = upper_bound(cow_fav[i].begin(), cow_fav[i].end(), l_cnt[i]) - cow_fav[i].begin();
        int cnt2 = upper_bound(cow_fav[i].begin(), cow_fav[i].end(), r_cnt[i]) - cow_fav[i].begin();
        if (cows[cow].first == i && cows[cow].second <= r_cnt[i] && cnt2) cnt2--;

        if (cnt1 && cnt2) {
            if (cnt1 == 1 && cnt2 == 1) {
                tot_ans++;
                tot_combo = tot_combo * 2 % MOD;
            } else {
                tot_ans += 2;
                tot_combo = tot_combo * min(cnt1, cnt2) % MOD * (max(cnt1, cnt2) - 1) % MOD;
            }
        } else if (cnt1 || cnt2) {
            tot_ans++;
            tot_combo = tot_combo * (cnt1 + cnt2) % MOD;
        }
    }

    // solve for placing only towards the left
    int left_ans = 1;
    ll left_combo = 1;
    for (int i = 1; i <= n; i++) {
        int cnt1 = get_cnt(l_cnt[i], cow_fav[i]);
        if (cnt1) {
            left_ans++;
            left_combo = left_combo * cnt1 % MOD;
        }
    }

    if (left_ans == tot_ans) {
        tot_combo = (left_combo + tot_combo) % MOD;
    }

    if (max_cow < tot_ans) {
        max_cow = tot_ans;
        tot = tot_combo;
    } else if (max_cow == tot_ans) {
        tot += tot_combo;
        tot %= MOD;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> tasty[i];
    }

    for (int i = 0; i < m; i++) {
        int f, h; cin >> f >> h;
        cows[i] = {f, h};
        cow_fav[f].push_back(h);
    }

    for (int i = 1; i <= n; i++) {
        sort(cow_fav[i].begin(), cow_fav[i].end());
    }

    for (int i = 0; i < m; i++) {
        solve(i, false);
        solve(i, true);
    }

    tot *= modpow(2, MOD - 2);
    tot %= MOD;

    cout << max_cow << ' ' << tot << '\n';

    return 0;
}
