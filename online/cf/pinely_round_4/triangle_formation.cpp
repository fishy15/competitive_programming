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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

bool solve_three(const vector<ll> &a) {
    int n = sz(a);

    int min_three = INF;
    int max_three = -1;
    for (int i = 0; i + 3 <= n; i++) {
        if (a[i] + a[i+1] > a[i+2]) {
            min_three = min(min_three, i);
            max_three = max(max_three, i);
        }
    }

    return max_three - min_three >= 3;
}

bool any_works(const array<ll, 6> &a) {
    rep(i, 0, 6) {
        rep(j, i+1, 6) {
            rep(k, j+1, 6) {
                auto inc_until = [&] (int x) {
                    while (x == i || x == j || x == k) x++;
                    return x;
                };

                if (a[i] + a[j] > a[k]) {
                    int oi = inc_until(0);
                    int oj = inc_until(oi+1);
                    int ok = inc_until(oj+1);
                    if (a[oi] + a[oj] > a[ok]) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool solve_six(const vector<ll> &a) {
    int n = sz(a);

    for (int i = 0; i + 6 <= n; i++) {
        array vals = {
            a[i],   a[i+1], a[i+2],
            a[i+3], a[i+4], a[i+5]
        };
        
        if (any_works(vals)) {
            return true;
        }
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<ll> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;

        if (r - l > 60) {
            cout << "YES\n";
        } else {
            auto interval = vector<ll>(a.begin() + l, a.begin() + r);
            sort(all(interval));
            if (solve_three(interval) || solve_six(interval)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}
