#pragma GCC target("popcnt")

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

int to_int(int k, const string &s) {
    int res = 0;

    for (int i = k - 1; i >= 0; i--) {
        res <<= 1;
        res += s[i] - '0';
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        nums[i] = to_int(k, s);
    }

    int ans = k;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = min(ans, __builtin_popcount(nums[i] ^ nums[j]));
        }
    }

    cout << ans << '\n';

    return 0;
}
