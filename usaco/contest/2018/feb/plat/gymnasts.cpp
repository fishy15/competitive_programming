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

ll n;
ll ans;

int cnt;
vector<ll> p;

void factor(ll n) {
    if (n % 2 == 0) {
        p.push_back(2);
        while (n % 2 == 0) {
            n /= 2;
        }
        cnt++;
    }

    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            p.push_back(i);
            while (n % i == 0) {
                n /= i;
            }
            cnt++;
        }
    }

    if (n > 1) {
        p.push_back(n);
        cnt++;
    }
}

ll modpow(ll n, ll e) {
    if (e == 0) return 1;
    if (e == 1) return n % MOD;
    
    ll res = modpow(n, e / 2);

    if (e % 2 == 0) {
        return res * res % MOD;
    }
    
    return (res * res % MOD * n) % MOD;
}

ll totient(const vector<int> &pp) {
    ll ans = 1;
    for (int i = 0; i < cnt; i++) {
        if (pp[i] > 0) {
            ans *= (p[i] - 1) % MOD;
            ans %= MOD;
            ans *= modpow(p[i], pp[i] - 1);
            ans %= MOD;
        }
    }

    return ans % MOD;
}

void process(ll m) {
    vector<int> pp(cnt);
    ll nn = n / m;
    for (int i = 0; i < cnt; i++) {
        while (nn % p[i] == 0) {
            pp[i]++;
            nn /= p[i];
        }
    }

    ll val = totient(pp);
    val *= modpow(2, m) - 1;
    val %= MOD;
    ans += val;
    if (ans < 0) ans += MOD;
    if (ans >= MOD) ans -= MOD;
}

int main() {
    ifstream fin("gymnasts.in");
    ofstream fout("gymnasts.out");

    fin >> n;

    factor(n);

    for (ll i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            process(i);
            if (i * i != n) process(n / i);
        }
    }

    ans -= modpow(2, n) - 1;
    ans++;
    while (ans >= MOD) ans -= MOD;
    while (ans < 0) ans += MOD;
    fout << ans % MOD << '\n';

    return 0;
}
