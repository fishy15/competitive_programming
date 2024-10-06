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
#include <bitset>

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

constexpr int MAXN = 10'000'000;
bitset<MAXN+1> prime;
vector<int> primes;

void precomp() {
    prime[0] = prime[1] = true;
    rep(i, 2, MAXN+1) {
        if (!prime[i]) {
            primes.push_back(i);
            for (ll j = (ll) i * i; j <= MAXN; j += i) {
                prime[j] = true;
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;

    int ans = 0;
    bool has2 = false;
    rep(i, 0, sz(primes)) {
        auto p = primes[i];
        if (p + 2 <= n) { 
            if (primes[i+1] == p + 2) {
                ans++;
                has2 = true;
            }
        } else {
            break;
        }
    }

    if (has2) ans++;
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
