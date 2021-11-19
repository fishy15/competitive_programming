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
#define MAXN 2010

using namespace std;

struct point {
    ll x, y;

    bool operator<(const point &p2) const {
        if (x == p2.x) {
            return y < p2.y;
        }
        return x < p2.x;
    }

    point operator-(const point &p2) const {
        return {x - p2.x, y - p2.y};
    }
};

int n;
point pts[MAXN];
int used[MAXN];
string s;

ll cross(const point &p1, const point &p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

bool ccw(const point &a, const point &b, const point &c) {
    return cross(b - a, c - b) > 0;
}

bool cw(const point &a, const point &b, const point &c) {
    return cross(b - a, c - b) < 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    int start = 0;
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
        if (pts[i] < pts[start]) {
            start = i;
        }
    }

    cin >> s;

    used[start] = 1;
    
    vector<int> ans;
    ans.push_back(start);

    int cur = start;
    for (int i = 0; i < n - 2; i++) {
        int l_most = -1;
        int r_most = -1;

        for (int j = 0; j < n; j++) {
            if (used[j] == 0) {
                if (l_most == -1) {
                    l_most = j;
                    r_most = j;
                } else if (cw(pts[cur], pts[r_most], pts[j])) {
                    r_most = j;
                } else if (ccw(pts[cur], pts[l_most], pts[j])) {
                    l_most = j;
                }
            }
        }

        if (s[i] == 'L') {
            used[r_most] = i + 2;
            ans.push_back(r_most);
            cur = r_most;
        } else {
            used[l_most] = i + 2;
            ans.push_back(l_most);
            cur = l_most;
        }
    }

    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            ans.push_back(i);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << ' ';
    }

    cout << '\n';

    return 0;
}
