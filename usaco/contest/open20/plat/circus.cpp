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
#define MAXN 100000

using namespace std;

int n;
vector<int> adj[MAXN - 1];

ll modpow(ll x, ll e, ll m) {
    if (e == 0) return 1LL;
    if (e == 1) return x % m;
    ll res = modpow(x, e / 2, m);
    if (e & 1) {
        return ((res * res) % m * x) % m;
    }
    return (res * res) % m;
}

ll inv(int x) {
    return modpow(x, MOD - 2, MOD);
}

int main() {
    ifstream fin("circus.in");
    ofstream fout("circus.out");

    fin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; fin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> div;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() > 2) {
            div.push_back(adj[i].size() - 1);
        }
    }

    ll f = 1;
    for (int i = 1; i <= n; i++) {
        f *= i;
        if (i <= n - 2) {
            ll qq = f;
            for (int x : div) {
                qq /= x;
            }
            fout << max(qq, 1LL) << '\n';
        } else {
            fout << f << '\n';
        }
    }

    return 0;
}
