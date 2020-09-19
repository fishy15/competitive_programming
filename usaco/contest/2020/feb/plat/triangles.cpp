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
#define MAXN 300

using namespace std;

ll n;
string grid[MAXN];

// down left
ll pre[MAXN + 1][MAXN + 1];
// down right
ll pre2[MAXN + 1][MAXN + 1];

ll pre1_get(ll i, ll j) {
    if (i >= n) {
        ll s = i + j;
        i = n - 1;
        j = s - i;
    }

    if (j < 0) {
        ll s = i + j;
        j = 0;
        i = s - j;
    }

    if (j >= n || i < 0) {
        return 0;
    }

    return pre[i + 1][j + 1];
}

ll pre2_get(ll i, ll j) {
    if (i >= n) {
        ll d = i - j;
        i = n - 1;
        j = i - d;
    }

    if (j >= n) {
        ll d = i - j;
        j = n - 1;
        i = j + d;
    }

    if (i < 0 || j < 0) {
        return 0;
    }

    return pre2[i + 1][j + 1];
}

int main() {
    ifstream fin("triangles.in");
    ofstream fout("triangles.out");

    fin >> n;
    for (ll i = 0; i < n; i++) {
        fin >> grid[i];
    }

    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            if (grid[i - 1][j - 1] == '*') {
                pre[i][j] = pre[i - 1][j + 1] + 1;
            } else {
                pre[i][j] = pre[i - 1][j + 1];
            }
        }
    }    

    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            if (grid[i - 1][j - 1] == '*') {
                pre2[i][j] = pre2[i - 1][j - 1] + 1;
            } else {
                pre2[i][j] = pre2[i - 1][j - 1];
            }
        }
    }

    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (grid[i][j] == '*') {
                ll d = 1;
                while (i + d < n && j - d >= 0) {
                    if (grid[i + d][j - d] == '*') {
                        pair<ll, ll> r = {i + d, j + d};
                        pair<ll, ll> dd = {i + 2 * d - 1, j + 1};
                         ans += pre1_get(dd.first, dd.second) - pre1_get(r.first, r.second);

                        r = {i - d, j - d};
                        dd = {i - 1, j - 2 * d + 1};
                        ans += pre1_get(dd.first, dd.second) - pre1_get(r.first, r.second);
                    }
                    d++;
                }

                d = 1;
                while (i + d < n && j + d < n) {
                    if (grid[i + d][j + d] == '*') {
                        pair<ll, ll> l = {i + d, j - d};
                        pair<ll, ll> dd = {i + 2 * d - 1, j - 1};
                        ans += pre2_get(dd.first, dd.second) - pre2_get(l.first, l.second);

                        l = {i - d, j + d};
                        dd = {i - 1, j + 2 * d - 1};
                        ans += pre2_get(dd.first, dd.second) - pre2_get(l.first, l.second);
                    }
                    d++;
                }

                d = 1;
                while (i + d < n && j + d < n && j - d >= 0) {
                    if (grid[i + d][j + d] == '*' && grid[i + d][j - d] == '*') {
                        ans++;
                    }
                    d++;
                }

                d = 1;
                while (j - d >= 0 && i + d < n && i - d >= 0) {
                    if (grid[i + d][j - d] == '*' && grid[i - d][j - d] == '*') {
                        ans++;
                    }
                    d++;
                }

                d = 1;
                while (i - d >= 0 && j + d < n && j - d >= 0) {
                    if (grid[i - d][j + d] == '*' && grid[i - d][j - d] == '*') {
                        ans++;
                    }
                    d++;
                }

                d = 1;
                while (j + d < n && i + d < n && i - d >= 0) {
                    if (grid[i + d][j + d] == '*' && grid[i - d][j + d] == '*') {
                        ans++;
                    }
                    d++;
                }

            }
        }
    }

    fout << ans << '\n';

    return 0;
}
