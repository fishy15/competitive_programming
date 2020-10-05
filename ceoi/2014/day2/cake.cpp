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
#define MAXN 250010

using namespace std;

int n, a;
int q;
int front_bit[MAXN];
int back_bit[MAXN];
int nums[MAXN];
int sz;
vector<int> top;
int curmax;

void upd(int x, int v, int* bit) {
    while (x < MAXN) {
        bit[x] = max(bit[x], v);
        x += x & -x;
    }
}

int qry_max(int x, int* bit) {
    int ans = 0;
    while (x) {
        ans = max(ans, bit[x]);
        x -= x & -x;
    }
    return ans;
}

int qry_len(int mm, int* bit) {
    int m = 0;
    int pos = 0;
    for (int i = 18; i >= 0; i--) {
        if (pos + (1 << i) < MAXN && max(m, bit[pos + (1 << i)]) <= mm) {
            pos += 1 << i;
            m = max(m, bit[pos]);
        }
    }
    return pos;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> a;
    a--;
    curmax = n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    sz = min(n, 10);
    top.resize(sz);

    for (int i = 0; i < n; i++) {
        if (nums[i] > n - sz) {
            top[n - nums[i]] = i;
        }
    }

    for (int i = a - 1; i >= 0; i--) {
        upd(a - i, nums[i], front_bit);
    }

    for (int i = a + 1; i < n; i++) {
        upd(i - a, nums[i], back_bit);
    }

    cin >> q;
    while (q--) {
        char t; cin >> t;
        if (t == 'F') {
            int x; cin >> x;
            x--;
            if (x < a) {
                int ans = a - x;
                int mm = qry_max(a - x, front_bit);
                ans += min(qry_len(mm, back_bit), n - a - 1);
                cout << ans << '\n';
            } else if (x > a) {
                int ans = x - a;
                int mm = qry_max(x - a, back_bit);
                ans += min(qry_len(mm, front_bit), a);
                cout << ans << '\n';
            } else {
                cout << "0\n";
            }
        } else {
            int i, e; cin >> i >> e;
            i--; e--;

            auto it = find(top.begin(), top.end(), i);
            if (it != top.end()) {
                top.erase(it);
            }
            top.insert(top.begin() + e, i);
            if (top.size() > sz) top.pop_back();

            for (int j = 1; j <= sz; j++) {
                if (top[sz - j] < a) {
                    upd(a - top[sz - j], curmax + j, front_bit);
                } else if (top[sz - j] > a) {
                    upd(top[sz - j] - a, curmax + j, back_bit);
                }
            }
            curmax += sz;
        }
    }

    return 0;
}
