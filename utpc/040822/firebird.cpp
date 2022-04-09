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

int n, k;
vector<int> nums;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    int cur = 0;
    int ans = 0;
    for (int i = 1; i < n; i++) {
        cur++;

        if (nums[i] != -1) {
            while (cur < nums[i]) {
                cur += k;
                ans--;
            }
        }

        if (cur >= k) {
            cur = 0;
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}
