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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> nums(3 * n);
    rep(i, 0, 3 * n) {
        cin >> nums[i];
    }

    sort(all(nums));

    auto p1 = accumulate(begin(nums) + n, end(nums), 0LL);
    auto p2 = accumulate(begin(nums), begin(nums) + n, 0LL) * 3;

    cout << p1 << ' ' << p2 << '\n';

    return 0;
}
