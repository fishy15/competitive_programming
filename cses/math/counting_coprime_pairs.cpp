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

int pp[MAXN + 1];

void precalc() {
    for (ll i = 2; i <= MAXN; i++) {
        if (pp[i] == 0) {
            pp[i] = i;
            for (ll j = i * i; j <= MAXN; j += i) {
                pp[j] = i;
            }
        }
    }
}

vector<int> factor(int x) {
    set<int> s;
    while (x > 1) {
        s.insert(pp[x]);
        x /= pp[x];
    }
    return vector<int>(s.begin(), s.end());
}


void recurse(const vector<int> &nums, int idx, int added, int mul, vector<int> &count, vector<int> &sz) {
    if (idx == (int) nums.size()) {
        count[mul]++;
        sz[mul] = added;
    } else {
        recurse(nums, idx + 1, added, mul, count, sz);
        recurse(nums, idx + 1, added + 1, mul * nums[idx], count, sz);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<int> count(MAXN + 1);
    vector<int> sz(MAXN + 1, -1);

    for (auto x : nums) {
        auto ps = factor(x);
        recurse(ps, 0, 0, 1, count, sz);
    }

    ll ans = 0;
    for (int i = 1; i <= MAXN; i++) {
        if (sz[i] != -1) {
            auto sgn = (sz[i] % 2 == 0) ? 1 : -1;
            auto combo = (ll) count[i] * (count[i] - 1) / 2;
            ans += combo * sgn;
        }
    }

    cout << ans << '\n';

    return 0;
}
