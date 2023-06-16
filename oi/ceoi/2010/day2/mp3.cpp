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
#define MAXN 100010

using namespace std;

int n, vmax, v2;
pair<int, int> nums[MAXN];
map<int, vector<pair<int, int>>> m;
bool assign;
map<int, vector<pair<int, int>>>::iterator ans;

struct f {
    int a, b;
    int init;
    f(int a, int b, int c) : a(a), b(b), init(c) {}
    f() : f(1, 1001, 1) {}
    int operator()(int x) const {
        if (x <= a) return init;
        else if (x <= b) return init + (x - a);
        else return init + b - a;
    }
    f operator*(const f &f2) const {
        if (init <= f2.a) {
            if (init + b - a <= f2.a) {
                return f(vmax, vmax, f2(init));
            } else if (init + b - a <= f2.b) {
                int x = f2.a - init + a;
                return f(x, b, f2(init));
            } else {
                int x = f2.a - init + a;
                int y = x + f2.b - f2.a;
                return f(x, y, f2(init));
            }
        } else if (init <= f2.b) {
            if (init + b - a <= f2.b) {
                return f(a, b, f2(init));
            } else {
                int y = a + f2.b - init;
                return f(a, y, f2(init));
            }
        } else {
            return f(vmax, vmax, f2(init));
        }
    }
};

f st[4 * MAXN];
f ans_f;

void upd(int x, int sg, int v = 1, int l = 0, int r = n - 2) {
    if (l == r) {
        if (sg == -1) {
            st[v] = f(2, vmax, 1);
        } else {
            st[v] = f(1, vmax - 1, 2);
        }
    } else {
        int m = (l + r) / 2;
        if (x <= m) {
            upd(x, sg, 2 * v, l, m);
        } else {
            upd(x, sg, 2 * v + 1, m + 1, r);
        }
        st[v] = st[2 * v] * st[2 * v + 1];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> vmax >> v2;
    for (int i = 0; i < n; i++) {
        char c; int x; cin >> c >> x;
        if (c == '+') nums[i] = {x, 1};
        else nums[i] = {x, -1};
    }

    for (int i = 1; i < n; i++) {
        m[nums[i].first - nums[i - 1].first].push_back({i - 1, nums[i].second});
    }

    for (auto it = m.begin(); it != m.end(); it++) {
        for (auto p : it->second) {
            upd(p.first, p.second);
        }
        if (st[1].init <= v2 && v2 <= st[1].init + (st[1].b - st[1].a)) {
            ans = it;
            ans_f = st[1];
            assign = true;
        }
    }

    if (!assign) {
        cout << m.begin()->first - 1 << ' ';
        cout << v2 << '\n';
        return 0;
    }

    ans = next(ans);
    if (ans == m.end()) {
        cout << "infinity\n";
        return 0;
    } 
        
    cout << ans->first - 1 << ' ';

    for (int i = 1; i <= vmax; i++) {
        if (ans_f(i) == v2) {
            cout << i << '\n';
            return 0;
        }
    }

    return 0;
}
