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

int nums[MAXN][2];
multiset<int> cur_b;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    ll ans = INFLL;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        nums[i][0] = a;
        nums[i][1] = b;
        cur_b.insert(b);
    }

    for (int i = 0; i < n; i++) {
        ans = min<ll>(ans, nums[i][0] + nums[i][1]);
        cur_b.erase(cur_b.find(nums[i][1]));
        ans = min<ll>(ans, max(nums[i][0], *cur_b.begin()));
        cur_b.insert(nums[i][1]);
    }

    cout << ans << '\n';

    return 0;
}
