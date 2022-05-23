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
#define MAXN 100010

using namespace std;

int n, t;
int nums[MAXN];

bool check(int k) {
    array<int, 3> cnt{};
    for (int i = 0; i < n; i++) {
        if (10 * nums[i] >= 9 * k) {
            cnt[0]++;
        }

        if (10 * nums[i] >= 8 * k) {
            cnt[1]++;
        }

        if (10 * nums[i] >= 7 * k) {
            cnt[2]++;
        }
    }

    return 4 * cnt[0] >= 1 * n && 4 * cnt[1] >= 2 * n && 4 * cnt[2] >= 3 * n;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> t;
    
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int l = 1;
    int r = t * 100;
    int a = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) {
            a = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    cout << a << '\n';

    return 0;
}
