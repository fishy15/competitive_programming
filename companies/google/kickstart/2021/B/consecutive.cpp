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
#define MAXN 1000000

using namespace std;

bool is_prime(ll n) {
    ll sq = sqrt(n);
    for (ll i = 2; i <= sq; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

ll p_le(ll n) {
    n--;
    while (n >= 2) {
        if (is_prime(n)) return n;
        n--;
    }
    return 1;
}

ll p_ge(ll n) {
    n++;
    while (true) {
        if (is_prime(n)) return n;
        n++;
    }
}

void solve() {
    ll n; cin >> n;
    vector<ll> poss;
    
    ll sq = sqrt(n);
    ll hi_sq = p_ge(sq);
    ll lo_sq = p_le(sq);
    ll lo_lo = p_le(lo_sq);

    vector<ll> nums = {hi_sq, lo_sq, lo_lo};
    if (is_prime(sq)) nums.push_back(sq);

    sort(nums.begin(), nums.end());

    for (int i = nums.size() - 2; i >= 0; i--) {
        ll p = nums[i] * nums[i + 1];
        if (p <= n) {
            cout << p << '\n';
            return;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
