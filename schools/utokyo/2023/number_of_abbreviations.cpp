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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    string s;
    cin >> n >> s;

    auto tri = [&](int n) {
        return (ll) n * (n + 1) / 2;
    };

    auto ans = tri(n);

    array<int, 26> cnt{};
    for (auto c : s) {
        cnt[c - 'a']++;
    }

    rep(i, 0, 26) {
        if (cnt[i] > 0) {
            ans -= tri(cnt[i] - 1);
        }
    }

    cout << ans << '\n';

    return 0;
}
