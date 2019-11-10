// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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

ll gcd(ll x, ll y) {
    if (y > x) {
        swap(x, y);
    } 
    
    if (y == 0) {
        return x;
    }
    
    return gcd(y, x % y);
}

void solve() {
    ll n; cin >> n;
    vector<ll> tickets;

    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        tickets.push_back(x / 100);
    }

    ll x, a; cin >> x >> a;
    ll y, b; cin >> y >> b;
    ll k; cin >> k;

    sort(tickets.rbegin(), tickets.rend());

    ll l = 0, r = n;
    ll ans = -1;
    while (l <= r) {
        ll mid = l + (r - l) / 2;
        //cout << mid << '\n';
        ll both = mid * gcd(a, b) / a / b;
        ll only_a = mid / a - both;
        ll only_b = mid / b - both;

        //cout << both << ' ' << only_a << only_b << '\n';

        ll sum1 = 0;
        ll sum2 = 0;
        ll pos = 0;
        for (int i = 0; i < both; i++) {
            sum1 += tickets[i] * (x + y);
            sum2 += tickets[i] * (x + y);
            pos++;
        }
        
        //cout << '\t' << pos << '\n';

        for (int i = 0; i < only_a; i++) {
            if (pos < n)
                sum1 += tickets[pos] * x;
            if (pos + only_b < n)
                sum2 += tickets[pos + only_b] * x;
            pos++;
        }
       // cout << '\t' << pos << '\n';

        for (int i = 0; i < only_b; i++) {
            if (pos < n)
                sum1 += tickets[pos] * y;
            if (pos - only_a < n && pos - only_a >= 0)
                sum2 += tickets[pos - only_a] * y;
            pos++;
        }

        if (max(sum1, sum2) >= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
        
        //cout << mid << ' ' << sum1 << ' ' << sum2 << '\n';
    }
    
    cout << ans << '\n';
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int q; cin >> q;
    while (q--) {
        solve();
    }

    return 0;
}
