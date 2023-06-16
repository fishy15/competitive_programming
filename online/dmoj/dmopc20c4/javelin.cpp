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
#include <list>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 5010

using namespace std;

int n;
int a[MAXN];
vector<vector<int>> same_grp;

struct BIT {
    int bit[MAXN];

    void upd(int x, int v) {
        while (x < MAXN) {
            bit[x] += v;
            x += x & -x;
        }
    }

    int qry(int x) {
        int res = 0;
        while (x) {
            res += bit[x];
            x -= x & -x;
        }
        return res;
    }

    void reset() {
        memset(bit, 0, sizeof bit);
    }
} bit;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    same_grp.push_back({1});
    cout << '0';

    for (int i = 1; i < n; i++) {
        vector<vector<int>> nxt;
        int diff = a[i] - (int)(same_grp.size());
        for (auto &v : same_grp) {
            while (diff > 0 && v.size() > 1) {
                nxt.push_back({v.back()});
                v.pop_back();
                diff--;
            }
            nxt.push_back(v);
        }

        same_grp.swap(nxt);

        if (a[i] == (int)(same_grp.size())) {
            same_grp.push_back({i + 1});
        } else {
            same_grp[a[i]].push_back(i + 1);
        }

        ll ans = 0;
        bit.reset();
        for (auto it = same_grp.rbegin(); it != same_grp.rend(); it++) {
            for (int x : *it) {
                ans += bit.qry(x);
            }
            for (int x : *it) {
                bit.upd(x, 1);
            }
        }

        cout << ' ' << ans;
    }

    cout << '\n';

    return 0;
}
