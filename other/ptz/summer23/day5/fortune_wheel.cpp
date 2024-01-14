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

struct frac {
    ll num;
    ll denom;

    frac(ll n, ll d) {
        auto g = gcd(n, d);
        num = n / g;
        denom = d / g;
    }

    frac operator+(const frac &f2) const {
        return {num * f2.denom + f2.num * denom, denom * f2.denom};
    }

    bool operator<(const frac &f2) const {
        return (__int128) num * f2.denom < (__int128) f2.num * denom;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, x, k;
    cin >> n >> x >> k;

    vector<int> nums(k);
    for (auto &x : nums) {
        cin >> x;
    }

    vector<int> d(n, INF);
    vector<int> cnt_at(n + 1);
    queue<int> q;

    d[0] = 0;
    q.push(0);

    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        
        cnt_at[d[v]]++;

        for (auto p : nums) {
            auto nxt = v - p;
            if (nxt < 0) nxt += n;
            if (d[nxt] == INF) {
                d[nxt] = d[v] + 1;
                q.push(nxt);
            }
        }
    }

    // choosing random always
    frac ans = {n, 1};

    // go direct
    if (d[x] != INF) {
        ans = min(ans, {d[x], 1});
    }

    // go random than direct
    int works = 0;
    ll sum_works = 0;
    for (int i = 0; i <= n; i++) {
        works += cnt_at[i];
        sum_works += (ll) i * cnt_at[i];

        // n / works moves + sum_works / works moves
        ans = min(ans, frac(n, works) + frac(sum_works, works));
    }

    cout << ans.num << ' ' << ans.denom << '\n';

    return 0;
}
