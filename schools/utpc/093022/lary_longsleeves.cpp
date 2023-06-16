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
#define MAXN 2000200

using namespace std;

bool p[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    fill(p, p + MAXN, true);
    p[0] = false;
    p[1] = false;

    for (ll i = 2; i < MAXN; i++) {
        if (p[i]) {
            for (ll j = i * i; j < MAXN; j += i) {
                p[j] = false;
            }
        }
    }

    int n, m;
    cin >> n >> m;

    set<int> a, b;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.insert(x);
    }

    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        b.insert(x);
    }

    vector<int> to_check;
    for (int x : a) {
        if (b.count(x - 1)) {
            to_check.push_back(2 * x - 1);
        }

        if (b.count(x + 1)) {
            to_check.push_back(2 * x + 1);
        }
    }

    int ans = -1;
    for (int x : to_check) {
        if (p[x]) {
            ans = max(ans, x);
        }
    }

    cout << ans << '\n';

    return 0;
}
