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
    int n;
    cin >> n;

    vector<pair<int, int>> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i].first;
    }
    for (int i = 0; i < n; i++) {
        cin >> nums[i].second;
    }

    sort(nums.begin(), nums.end(), [](auto p1, auto p2) {
        return (p1.first + p1.second) < (p2.first + p2.second);
    });

    for (int i = 0; i < n; i++) {
        cout << nums[i].first << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        cout << nums[i].second << ' ';
    }
    cout << '\n';
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
