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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < n; i++) {
        pq.push({nums[i], i});
    }

    vector<bool> vis(n);
    while (!pq.empty()) {
        auto [_, i] = pq.top();
        pq.pop();

        if (vis[i]) continue;
        vis[i] = true;

        if (i > 0) {
            if (nums[i - 1] < nums[i] - m) {
                nums[i - 1] = nums[i] - m;
                pq.push({nums[i - 1], i - 1});
            }
        }

        if (i < n - 1) {
            if (nums[i + 1] < nums[i] - m) {
                nums[i + 1] = nums[i] - m;
                pq.push({nums[i + 1], i + 1});
            }
        }
    }

    for (auto x : nums) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
