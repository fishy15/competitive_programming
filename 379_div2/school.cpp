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
#define MAXN 200010

using namespace std;

int n;
ll a[MAXN];
ll b[MAXN];
ll c[MAXN];
ll s[MAXN];
ll tot;

ll cnt[70];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    for (int i = 0; i < n; i++) {
        s[i] = b[i] + c[i];
        tot += s[i];
    }

    tot /= 2 * n;

    for (int i = 0; i < n; i++) {
        a[i] = (s[i] - tot) / n;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 60; j++) {
            cnt[j] += (a[i] & (1LL << j)) > 0;
        }
    }

    for (int i = 0; i < n; i++) {
        ll aa = 0;
        ll oo = 0;

        for (int j = 0; j < 60; j++) {
            if (a[i] & (1LL << j)) {
                aa += cnt[j] * (1LL << j);
                oo += n * (1LL << j);
            } else {
                oo += cnt[j] * (1LL << j);
            }
        }

        if (aa != b[i] || oo != c[i]) {
            cout << "-1\n";
            return 0;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';

    return 0;
}
