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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, d;
    cin >> n >> d;

    vector<ll> nums(n);
    vector<ll> pts;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < n - 1; i++) {
        auto [a, b] = minmax(nums[i], nums[i + 1]);
        pts.push_back(a - d);
        pts.push_back(a);
        pts.push_back(b);
        pts.push_back(b - d);
    }

    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    ll ans = 0;
    for (auto l : pts) {
        auto r = l + d;

        ll cur = 0;
        for (int i = 0; i < n - 1; i++) {
            auto a = clamp(nums[i], l, r);
            auto b = clamp(nums[i + 1], l, r);
            cur += abs(a - b);
        }

        ans = max(ans, cur);
    }

    cout << ans << '\n';

    return 0;
}
