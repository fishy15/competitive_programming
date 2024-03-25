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
#define MOD 9302023

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

array<string, 10> names = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
};

struct mi {
    int v;
    mi(int _v) : v(_v) {
        if (v < 0) v += MOD;
        if (v >= MOD) v -= MOD;
    }
    mi(ll _v) : v(_v % MOD) {}

    mi operator+(const mi &other) const { return mi(v + other.v); }
};

pair<int, mi> comb(pair<int, mi> a, pair<int, mi> b) {
    if (a.first < b.first) {
        return a;
    } else if (a.first == b.first) {
        return {a.first, a.second + b.second};
    } else {
        return b;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    cin >> s;

    int n = s.size();

    vector<pair<int, mi>> dp(n+1, {INF, 0});
    dp[0] = {0, 1};

    for (int i = 0; i < n; i++) {
        dp[i+1] = dp[i];
        dp[i+1].first++;
        for (const auto &num : names) {
            if (i >= (int) num.size() - 1 && s.substr(i - num.size() + 1, num.size()) == num) {
                auto p = dp[i+1 - num.size()];
                p.first++;
                dp[i+1] = comb(dp[i+1], p);
            }
        }
    }

    cout << dp[n].first << '\n';
    cout << dp[n].second.v << '\n';

    return 0;
}
