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

constexpr int MAXN = 100'000;
bool prime[MAXN+1];

void precomp() {
    fill(all(prime), true);
    prime[0] = false;
    prime[1] = false;
    for (ll i = 2; i <= MAXN; i++) {
        if (prime[i]) {
            for (ll j = i * i; j <= MAXN; j += i) {
                prime[j] = false;
            }
        }
    }
}

int ceildiv(int n, int k) {
    return (n + k - 1) / k;
}

int floordiv(int n, int k) {
    return n / k;
}

void solve() {
    int n;
    cin >> n;

    vector<int> perm;
    if (n == 2) {
        cout << "2 1\n";
        return;
    } else if (n == 3) {
        cout << "2 1 3\n";
        return;
    }

    int target = n / 2;
    while (!prime[target]) {
        target--;
    }

    set<int> unused;
    rep(i, 1, n+1) {
        unused.insert(i);
    }

    perm = {target};
    unused.erase(target);
    for (int i = 1; i < 2 * target - i; i++) {
        perm.push_back(2 * target - i);
        perm.push_back(i);
        unused.erase(2 * target - i);
        unused.erase(i);
    }

    for (auto x : unused) {
        perm.push_back(x);
    }

    for (auto x : perm) {
        cout << x << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
