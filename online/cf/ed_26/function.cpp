// :pray: :steph:
// :pray: :bakekaga:

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

ll gcd(ll a, ll b) {
    if (a < b) {
        return gcd(b, a);
    } if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

vector<ll> p_div(ll a) {
    vector<ll> ans;
    if (a % 2 == 0) {
        ans.push_back(2);
        while (a % 2 == 0) a /= 2;
    }

    for (int i = 3; i <= sqrt(a); i += 2) {
        if (a % i == 0) {
            ans.push_back(i);
            while (a % i == 0) a /= i;
        }
    }

    if (a != 1) {
        ans.push_back(a);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll a, b; cin >> a >> b;

    ll ans = 0;
    while (b > 0) {
        ll g = gcd(a, b);
        a /= g;
        b /= g;
        auto p = p_div(a);
        if (p.size() == 0) {
            ans += b;
            break;
        } else {
            ll mindiff = INFLL;
            for (ll x : p) {
                mindiff = min(mindiff, b % x);
            } 
            ans += mindiff;
            b -= mindiff;
        }
    }

    cout << ans << '\n';

    return 0;
}
