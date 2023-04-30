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

vector<pair<ll, int>> factor(ll x) {
    vector<pair<ll, int>> ans;

    if (x % 2 == 0) {
        ans.push_back({2, 0});
        while (x % 2 == 0) {
            ans.back().second++;
            x /= 2;
        }
    }

    for (ll i = 3; i * i <= x; i += 2) {
        if (x % i == 0) {
            ans.push_back({i, 0});
            while (x % i == 0) {
                ans.back().second++;
                x /= i;
            }
        }
    }

    if (x > 1) {
        ans.push_back({x, 1});
    }

    return ans;
}

vector<ll> divisors(ll x) {
    vector<ll> ans;

    for (ll i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            ans.push_back(i);
            if (i * i != x) {
                ans.push_back(x / i);
            }
        }
    }

    sort(ans.begin(), ans.end());
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll x;
    cin >> x;

    auto pf = factor(x);
    ll div_x = 1;
    int ans = 0;

    // multiply by at least one
    for (auto [p, c] : pf) {
        for (int i = 0; i < c - 1; i++) {
            div_x *= p;
        }

        ans++;
    }

    auto div = divisors(div_x);
    int n = div.size();

    auto rdiv = [&](ll x) { 
        return lower_bound(div.begin(), div.end(), x) - div.begin();
    };

    vector<bool> is_p(n, false);
    for (int i = 0; i < n; i++) {
        is_p[i] = count_if(pf.begin(), pf.end(), [&](auto p) {
            return p.first == div[i];
        });
    }

    vector<vector<int>> dp(n, vector<int>(n));
    int best = 0;

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (!is_p[j] && div[i] % div[j] == 0) {
                dp[i][j] = max(dp[i][j - 1], dp[rdiv(div[i] / div[j])][j - 1] + 1);
            } else {
                dp[i][j] = dp[i][j - 1];
            }

            best = max(best, dp[i][j]);
        }
    }

    cout << best + ans << '\n';

    return 0;
}
