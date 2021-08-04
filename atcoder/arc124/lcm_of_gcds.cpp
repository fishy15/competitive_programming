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

int n;
vector<array<ll, 2>> nums;
map<ll, ll> first;
map<ll, ll> second;

void recurse(int l, int r, ll a, ll b, map<ll, ll> &m) {
    if (l == r) {
        m[a] = max(m[a], b);
        m[b] = max(m[b], a);
    } else {
        recurse(l + 1, r, gcd(a, nums[l][0]), gcd(b, nums[l][1]), m);
        recurse(l + 1, r, gcd(a, nums[l][1]), gcd(b, nums[l][0]), m);
    }
}

void create(int l, int r, map<ll, ll> &m) {
    recurse(l + 1, r, nums[l][0], nums[l][1], m);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    nums.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i][0] >> nums[i][1];
    }

    if (n == 1) {
        cout << lcm(nums[0][0], nums[0][1]) << '\n';
        return 0;
    }

    create(0, n / 2, first);
    create(n / 2, n, second);

    ll ans = 0;
    for (auto [fx, fy] : first) {
        for (auto [sx, sy] : second) {
            ans = max({ans, lcm(gcd(fx, sx), gcd(fy, sy)), lcm(gcd(fx, sy), gcd(fy, sx))});
        }
    }

    cout << ans << '\n';

    return 0;
}
