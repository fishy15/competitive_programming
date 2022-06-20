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

struct DSU {
    vector<int> dsu;
    vector<int> sz;

    DSU(int n) {
        dsu.resize(n);
        sz.resize(n);
        iota(dsu.begin(), dsu.end(), 0);
        fill(sz.begin(), sz.end(), 1); 
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
        }
    }
};

bool conn(vector<int> &nums) {
    DSU dsu(30);
    for (int x : nums) {
        for (int i = 0; i < 30; i++) {
            if (x & (1 << i)) {
                for (int j = i + 1; j < 30; j++) {
                    if (x & (1 << j)) {
                        dsu.join(i, j);
                    }
                }
            }
        }
    }

    int cc = -1;
    for (int x : nums) {
        for (int i = 0; i < 30; i++) {
            if (x & (1 << i)) {
                int c = dsu.find(i);
                if (cc == -1) {
                    cc = c;
                } else if (cc != c) {
                    return false;
                }
            }
        }
    }

    return true;
}

int one_set(int x) {
    for (int i = 29; i >= 0; i--) {
        if (x & (1 << i)) {
            return i;
        }
    }

    return -1;
}

void solve() {
    int n; cin >> n;
    vector<int> nums(n);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (nums[i] == 0) {
            ans++;
            nums[i]++;
        }
    }

    if (conn(nums)) {
        cout << ans << '\n';
        for (int x : nums) cout << x << ' ';
        cout << '\n';
        return;
    } else {
        array<int, 2> d = {1, -1};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2; j++) {
                nums[i] += d[j];
                if (nums[i] != 0 && conn(nums)) {
                    cout << ans + 1 << '\n';
                    for (int x : nums) cout << x << ' ';
                    cout << '\n';
                    return;
                }
                nums[i] -= d[j];
            }
        }
    }

    int mm = -1;
    vector<int> max_bit;
    for (int i = 0; i < n; i++) {
        int ms = one_set(nums[i] & -nums[i]);
        if (ms > mm) {
            mm = ms;
            max_bit = {i};
        } else if (ms == mm) {
            max_bit.push_back(i);
        }
    }

    nums[max_bit[0]]--;
    nums[max_bit[1]]++;
    
    cout << ans + 2 << '\n';
    for (int x : nums) cout << x << ' ';
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
