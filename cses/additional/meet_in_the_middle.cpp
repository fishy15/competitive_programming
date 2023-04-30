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
#define MAXN 1000000

using namespace std;

int n;
ll x, ans;

int nums[50];
ll cur[1 << 20];
int mm[1 << 20];

void calc(map<int, int> &ans, int *nums, int sz) {
    for (int i = 0; i < sz; i++) {
        mm[1 << i] = nums[i];
    }
    for (int i = 0; i < (1 << sz); i++) {
        if (i) {
            int m = i ^ (i & -i);
            cur[i] = cur[m] + mm[i & -i];
        }
        if (cur[i] <= x) ans[cur[i]]++;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> x;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    map<int, int> m1, m2;
    calc(m1, nums, n / 2);
    calc(m2, nums + n / 2, n - n / 2);

    for (const auto &p : m1) {
        if (m2.count(x - p.first)) {
            ans += (ll) p.second * m2[x - p.first];
        }
    }

    cout << ans << '\n';

    return 0;
}
