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

void solve() {
    int n, m;
    cin >> n >> m;

    multiset<int> nums;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        nums.insert(a);
    }

    for (int i = 0; i < m; i++) {
        int b;
        cin >> b;
        nums.erase(nums.begin());
        nums.insert(b);
    }

    cout << accumulate(nums.begin(), nums.end(), 0LL) << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
