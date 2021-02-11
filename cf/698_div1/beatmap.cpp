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
#include <numeric>

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
vector<array<int, 3>> ans_p;
array<int, 3> pts[MAXN];
const ld PI = acosl(-1);

ld sz(const array<ll, 2> &v) {
    return sqrt(v[0] * v[0] + v[1] * v[1]);
}

ld angle(array<int, 3> a, array<int, 3> b, array<int, 3> c) {
    array<ll, 2> v1 = {a[0] - b[0], a[1] - b[1]};
    array<ll, 2> v2 = {b[0] - c[0], b[1] - c[1]};
    ll dot = v1[0] * v2[0] + v1[1] * v2[1];
    return dot < 0;
}

bool ok(int idx) {
    return idx >= 0 && idx < (int)(ans_p.size());
}

bool check(int loc) {
    for (int i = loc - 2; i <= loc; i++) {
        if (ok(i) && ok(i + 1) && ok(i + 2)) {
            if (!angle(ans_p[i], ans_p[i + 1], ans_p[i + 2])) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> pts[i][0] >> pts[i][1];
        pts[i][2] = i + 1;
    }

    sort(pts, pts + n);
    for (int i = 0; i < n; i++) {
        ans_p.push_back(pts[i]); 
        int cur = i;
        while (!check(cur)) {
            if (cur) {
                cur--;
                swap(ans_p[cur], ans_p[cur + 1]);
            } else {
                cout << "-1\n";
                return 0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans_p[i][2] << ' ';
    }
    cout << '\n';

    return 0;
}
