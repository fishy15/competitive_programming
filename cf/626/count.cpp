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
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, m, k; cin >> n >> m >> k;
    vector<ll> a;
    vector<ll> b;

    for (ll i = 0; i < n; i++) {
        ll x; cin >> x;
        a.push_back(x);
    }

    for (ll i = 0; i < m; i++) {
        ll x; cin >> x;
        b.push_back(x);
    }

    ll ans = 0;

    for (ll i = 1; i <= sqrt(k); i++) {
        if (k % i == 0) {
            ll j = k / i;

            // i x j
            if (i <= n && j <= m) {
                ll a1 = 0;
                ll a2 = 0;
                ll s1 = 0;
                ll s2 = 0;

                for (ll q = 0; q < i; q++) {
                    s1 += a[q];
                }

                if (s1 == i) a1++;

                for (ll q = i; q < n; q++) {
                    s1 += a[q] - a[q - i];
                    if (s1 == i) a1++;
                }

                for (ll q = 0; q < j; q++) {
                    s2 += b[q];
                }

                if (s2 == j) a2++;

                for (ll q = j; q < m; q++) {
                    s2 += b[q] - b[q - j];
                    if (s2 == j) a2++;
                }

                ans += a1 * a2;
            }

            if (i != j) {
                swap(i, j);
                if (i <= n && j <= m) {
                    ll a1 = 0;
                    ll a2 = 0;
                    ll s1 = 0;
                    ll s2 = 0;

                    for (ll q = 0; q < i; q++) {
                        s1 += a[q];
                    }

                    if (s1 == i) a1++;

                    for (ll q = i; q < n; q++) {
                        s1 += a[q] - a[q - i];
                        if (s1 == i) a1++;
                    }

                    for (ll q = 0; q < j; q++) {
                        s2 += b[q];
                    }

                    if (s2 == j) a2++;

                    for (ll q = j; q < m; q++) {
                        s2 += b[q] - b[q - j];
                        if (s2 == j) a2++;
                    }

                    ans += a1 * a2;
                }

                swap(i, j);
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
