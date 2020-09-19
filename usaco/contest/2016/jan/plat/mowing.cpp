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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100000

using namespace std;

struct segtree {
    int l, r;
    ll val;
    segtree* c[2];

    segtree(int a, int b) {
        l = a;
        r = b;
        val = 0;
        c[0] = nullptr;
        c[1] = nullptr;
    }

    ~segtree() {
        if (c[0]) delete c[0];
        if (c[1]) delete c[1];
    }

    void update(int idx, int v) {
        val += v;
        if (l != r) {
            int mid = l + (r - l) / 2;
            if (idx <= mid) {
                if (!c[0]) {
                    c[0] = new segtree(l, mid);
                }
                c[0]->update(idx, v);
            } else {
                if (!c[1]) {
                    c[1] = new segtree(mid + 1, r);
                }
                c[1]->update(idx, v);
            }
        }
    }

    int query(int x, int y) {
        if (x <= l && r <= y) {
            return val;
        }
        
        if (y < l || x > r) {
            return 0;
        }

        int v1 = (c[0] != nullptr) ? c[0]->query(x, y) : 0;
        int v2 = (c[1] != nullptr) ? c[1]->query(x, y) : 0;
        return v1 + v2;
    }
};

int n, t;
segtree* bit[MAXN + 20];
vector<array<int, 5>> lines;

void update(int t, int y, int v) {
    while (t < MAXN + 10) {
        if (!bit[t]) {
            bit[t] = new segtree(0, 1000000010);
        }
        bit[t]->update(y, v);
        t += t & -t;
    }
}

int query(int t, int y1, int y2) {
    int ans = 0;
    while (t > 0) {
        if (bit[t]) {
            ans += bit[t]->query(y1, y2);
        }
        t -= t & -t;
    }
    return ans;
}

int main() {
    ifstream fin("mowing.in");
    ofstream fout("mowing.out");

    fin >> n >> t;

    int prevx, prevy; fin >> prevx >> prevy;

    for (int i = 0; i < n - 1; i++) {
        int x, y; fin >> x >> y;
        int mm = min(prevx, x);
        int mmm = max(prevx, x);
        lines.push_back({mm, mmm, min(prevy, y), max(prevy, y), i + 1});
        if (mm != mmm) {
            lines.push_back({mmm, -1, min(prevy, y), max(prevy, y), i + 1});
        }
        prevx = x;
        prevy = y;
    }

    sort(lines.begin(), lines.end());

    int ans = 0;
    for (const auto &l : lines) {
        cout << ans << '\n';
        if (l[0] == l[1]) {
            if (l[4] > t) {
                int v = query(l[4] - t, l[2] + 1, l[3] - 1);
                ans += v > 0 ? v : 0;
            }
            if (l[4] + t < MAXN + 10) {
                int v1 = query(MAXN + 9, l[2] + 1, l[3] - 1);
                int v2 = query(l[4] + t, l[2] + 1, l[3] - 1);
                ans += v1 - v2 > 0 ? v1 - v2 : 0;
            }
        } else if (l[0] < l[1]) {
            update(l[4], l[2], 1);
        } else {
            update(l[4], l[2], -1);
        }
    }

    fout << ans << '\n';

    return 0;
}
