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
#define MAXN 200010

using namespace std;

int n, k;
int nums[MAXN];
ll ans;

bool in(const multiset<int> &cur, int val) {
    auto it = cur.lower_bound(val);
    return it != cur.end() && *it == val;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    multiset<int> cur;
    int r = 0;
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        while (r < n && (in(cur, nums[r]) || cnt + 1 <= k)) {
            if (!in(cur, nums[r])) cnt++;
            cur.insert(nums[r]);
            r++;
        }
        ans += r - i;
        cur.erase(cur.find(nums[i]));
        if (!in(cur, nums[i])) cnt--;
    }

    cout << ans << '\n';

    return 0;
}
