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
#define MAXN 1000000

using namespace std;

ll ans[MAXN + 1];

void precalc(){
    ans[1] = 1;
    int l = 2;
    int before = 1;

    while (before < MAXN) {
        ll first = before + 1;
        ll last = before + l;

        ll p_row_start = before - (l - 2);
        ll pp_row_start = p_row_start - (l - 2);

        if (first <= MAXN) {
            ans[first] = ans[p_row_start] + (first * first);
        }

        if (last <= MAXN) {
            ans[last] = ans[first - 1] + (last * last);
        }

        for (int i = 0; i < l - 2; i++) {
            ll cur = first + i + 1;
            ll left_knock = p_row_start + i;
            ll right_knock = p_row_start + i + 1;
            ll common = pp_row_start + i;

            if (cur <= MAXN) {
                ans[cur] = ans[left_knock] + ans[right_knock] - ans[common] + (cur * cur);
            }
        }

        before += l;
        l++;
    }
}

void solve() {
    int n;
    cin >> n;
    cout << ans[n] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
