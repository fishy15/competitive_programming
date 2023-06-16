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

void solve() {
    int n; cin >> n;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<array<int, 3>> mov;
    
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        if (nums[i - 1] > nums[i]) {
            cnt++;
        }
    }

    if (cnt > n / 2) {
        mov.push_back({3, n, (1 << 30) - 1});
        for (int i = 0; i < n; i++) {
            nums[i] ^= (1 << 30) - 1;
        }
    }

    for (int i = n - 1; i > 0; i--) {
        if (nums[i - 1] > nums[i]) {
            mov.push_back({2, i + 1, nums[i - 1] - nums[i]});
        }
    }

    cout << mov.size() << '\n';
    for (auto m : mov) {
        cout << m[0] << ' ' << m[1] << ' ' << m[2] << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
