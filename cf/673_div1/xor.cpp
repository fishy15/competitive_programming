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
#define MAXN 300010

using namespace std;

int n;
vector<int> nums;
ll ans;
ll pos[40][2];
int res;

void solve(vector<int> v, int idx) {
    int one = 0;
    int zero = 0;
    ll cnt = 0;
    ll cnt_1 = 0; // flip
    for (auto x : v) {
        if (x & (1 << idx)) {
            one++;
            cnt_1 += zero;
        } else {
            zero++;
            cnt += one;
        }
    }

    pos[idx][0] += cnt;
    pos[idx][1] += cnt_1;

    if (idx) {
        vector<int> v1, v2;
        for (auto x : v) {
            if (x & (1 << idx)) {
                v1.push_back(x);
            } else {
                v2.push_back(x);
            }
        }

        if (!v1.empty()) solve(v1, idx - 1);
        if (!v2.empty()) solve(v2, idx - 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    solve(nums, 30);

    for (int i = 30; i >= 0; i--) {
        if (pos[i][1] < pos[i][0]) {
            ans += pos[i][1];
            res += (1 << i);
        } else {
            ans += pos[i][0];
        }
    }

    cout << ans << ' ' << res << '\n';

    return 0;
}
