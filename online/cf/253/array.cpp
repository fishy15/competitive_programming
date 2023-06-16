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
#define MAXN 500010

using namespace std;

int n;
int vals[MAXN];
array<int, 2> nums[MAXN];
set<int> pos;
ll ans;

int before(int x) {
    auto it = pos.lower_bound(x);
    if (it == pos.begin()) {
        return -1;
    } else {
        return *prev(it);
    }
}

int after(int x) {
    auto it = pos.lower_bound(x);
    if (it == pos.end()) {
        return -1;
    } else {
        return *it;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i][0];
        vals[i] = nums[i][0];
        nums[i][1] = i;
        pos.insert(i);
    }

    sort(nums, nums + n);

    int sub = 0;
    for (int i = 0; i < n - 2; i++) {
        ans += (ll) (n - 2 - i) * (nums[i][0] - sub);
        sub = nums[i][0];

        pos.erase(nums[i][1]);
        int x = before(nums[i][1]);
        int y = after(nums[i][1]);

        if (x != -1 && y != -1) {
            ans += min(vals[x], vals[y]) - sub;
        }
    }

    cout << ans << '\n';

    return 0;
}
