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
#define MAXN 400010

using namespace std;

int n;
vector<int> child[MAXN];
int sz[MAXN];

int pp[MAXN];
int mul[MAXN];

void comb(map<int, int> &m1, map<int, int> &m2) {
    if (m1.size() < m2.size()) swap(m1, m2);
    for (auto p : m2) m1[p.first] += p.second;
    m2.clear();
}

map<int, int> factor(int x) {
    map<int, int> res;
    while (x > 1) {
        res[pp[x]]++;
        x /= pp[x];
    }
    return res;
}

void dfs(int v) {
    for (int c : child[v]) {
        dfs(c);
        sz[v] += sz[c] + 1;
        mul[sz[c] + 1]--;
    }
    mul[sz[v]]++;
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        child[x - 1].push_back(i + 1);
    }

    for (ll i = 2; i <= n; i++) {
        if (!pp[i]) {
            pp[i] = i;
            for (ll j = i * i; j <= n; j += i) {
                pp[j] = i;
            }
        }
    }

    dfs(0);
    map<int, ll> res;
    for (int i = n; i > 0; i--) {
        mul[i] += mul[i + 1];
        auto m = factor(i);
        for (auto p : m) {
            res[p.first] += mul[i] * p.second;
        }
    }

    vector<pair<int, ll>> v;
    for (auto p : res) {
        if (p.second != 0) {
            v.push_back(p);
        }
    }
    if (v.empty()) {
        cout << "0\n";
    } else {
        cout << v.size() << '\n';
        for (auto p : v) {
            cout << p.first << ' ' << p.second << '\n';
        }
    }

    return 0;
}
