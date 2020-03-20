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

ll modpow(ll n, ll e, ll m) {
    if (e == 0) return 1LL;
    if (e == 1) return n % m;
    ll res = modpow(n, e / 2, m);
    if (e % 2) {
        return (res * res % m) * n % m;
    }
    return res * res % m;
}

string pali(const string &s) {
    pair<ll, ll> h1;
    pair<ll, ll> h2;
    ll p1 = 31;
    ll p2 = 37;
    ll m1 = 1e9 + 9;
    ll m2 = 1e9 + 7;
    ll inv1 = modpow(p1, m1 - 2, m1);a
    ll inv2 = modpow(p2, m2 - 2, m2);
    int n = (int)(s.size());
    int ans = 0;
    cout << s << '\n';
    for (int i = 0; i < n; i++) {
        cout << h1.first << ' ' << h2.first << '\n';
        if (i % 2 == 0) {
            if (i > 0) {
                h2.first -= (s[i / 2 - 1] - 'a' + 1) * modpow(p1, i / 2 - 1, m1) % m1;
                h2.second -= (s[i / 2 - 1] - 'a' + 1) * modpow(p2, i / 2 - 1, m2) % m2;
                while (h2.first < 0) h2.first += m1;
                while (h2.second < 0) h2.second += m2;
            }
            h2.first *= p1;
            h2.first %= m1;
            h2.second *= p2;
            h2.second %= m2;
            h2.first += s[i] - 'a' + 1;
            h2.second += s[i] - 'a' + 1;
            if (h2.first > m1) h2.first -= m1;
            if (h2.second > m2) h2.second -= m2;

            if (h1 == h2) {
                string s1 = "";
                string s2 = "";
                for (int j = 0; j < i / 2; j++) {
                    s1 += s[j];
                }
                for (int j = i - 1; j > i / 2; j--) {
                    s2 += s[j];
                }
                cout << s1 << ' ' << s2 << '\n';

                if (s1 == s2) {
                    ans = i;
                }
            }
        } else {
            h1.first += (s[i / 2] - 'a' + 1) * modpow(p1, i / 2, m1) % m1;
            h1.second += (s[i / 2] - 'a' + 1) * modpow(p2, i / 2, m2) % m2;
            if (h1.first > m1) h1.first -= m1;
            if (h1.second > m2) h1.second -= m2;
            h2.first *= p1;
            h2.first %= m1;
            h2.second *= p2;
            h2.second %= m2;                
            h2.first += s[i] - 'a' + 1;
            h2.second += s[i] - 'a' + 1;
            if (h2.first > m1) h2.first -= m1;
            if (h2.first > m2) h2.second -= m2;

            if (h1 == h2) {
                string s1 = "";
                string s2 = "";
                for (int j = 0; j <= i / 2; j++) {
                    s1 += s[j];
                }
                for (int j = i; j > i / 2; j--) {
                    s2 += s[j];
                }

                cout << s1 << ' ' << s2 << '\n';

                if (s1 == s2) {
                    ans = i;
                }
            }
        }
    }

    return s.substr(0, ans);
}

void solve() {
    string s; cin >> s;
    int n = (int)(s.size());
    string cur = "";
    string cur2 = "";

    for (int i = 0; i <= n / 2; i++) {
        int j = n - 1 - i;
        if (i > j || s[i] != s[j]) break;
        if (i == j) {
            cur += s[i];
            break;
        }
        cur += s[i];
        cur2 += s[j];
    }

    int pos = (int)(cur.size());
    string mid = "";
    for (int i = 0; i < n - (int)(cur.size()) - (int)(cur2.size()); i++) {
        mid += s[pos + i];
    }

    string ans = pali(mid);
    reverse(mid.begin(), mid.end());
    string ans2 = pali(mid);

    if (ans.size() < ans2.size()) swap(ans, ans2);

    reverse(cur2.begin(), cur2.end());
    cout << cur << ans << cur2 << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;

    pali("aaaaaaa");
    while (t--) {
        solve();
    }

    return 0;
}
