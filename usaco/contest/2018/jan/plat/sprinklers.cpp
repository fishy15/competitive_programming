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

int n;
int pos[MAXN];
ll top[MAXN];
ll bottom[MAXN];
ll l[MAXN];

ll cnt[MAXN];
ll psum[MAXN];

int main() {
    ifstream fin("sprinklers.in");
    ofstream fout("sprinklers.out");

    fin >> n;

    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;
        pos[x] = y;
    }

    int cur = pos[n - 1];
    for (int i = n - 1; i > 0; i--) {
        cur = max(pos[i], cur);
        top[i - 1] = cur;
    }

    cur = pos[0];
    for (int i = 0; i < n; i++) {
        cur = min(cur, pos[i]);
        bottom[i] = cur;
    }

    int prev = n;
    for (int i = 0; i < n - 1; i++) {
        for (int j = prev - 1; j >= bottom[i]; j--) {
            l[j] = i;
        }
        prev = bottom[i];
    }

    for (int i = n - 2; i >= 0; i--) {
        cnt[i] = cnt[i + 1];
        cnt[i] += l[i];
        if (cnt[i] >= MOD) cnt[i] -= MOD;
    }

    for (int i = n - 2; i >= 0; i--) {
        psum[i] = psum[i + 1];
        psum[i] += ((n - i) * l[i]) % MOD;
        if (psum[i] >= MOD) psum[i] -= MOD;
    }

    ll ans = 0;
    for (int i = 0; i < n - 1; i++) {
        if (bottom[i] > top[i]) continue;
        ll tot = top[i] * (top[i] + 1) / 2 % MOD;
        tot -= bottom[i] * (bottom[i] + 1) / 2 % MOD;
        if (tot < 0) tot += MOD;
        tot *= (i + 1);
        tot %= MOD;

        ll bad_top = (psum[bottom[i]] - psum[top[i] + 1]) % MOD;
        if (bad_top >= MOD) bad_top -= MOD;
        bad_top -= (n - top[i]) * (cnt[bottom[i]] - cnt[top[i] + 1]) % MOD;
        if (bad_top < 0) bad_top += MOD;

        ll bad_bot = bottom[i] * (i + 1) % MOD * (top[i] - bottom[i]) % MOD;
        
        ans += tot;
        if (ans >= MOD) ans -= MOD;
        ans -= bad_top;
        if (ans < 0) ans += MOD;
        ans -= bad_bot;
        if (ans < 0) ans += MOD;
    }

    fout << ans << '\n';

    return 0;
}
