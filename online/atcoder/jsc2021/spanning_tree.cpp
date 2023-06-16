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

// change if necessary
#define MAXN 310

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

struct DSU {
    vector<int> dsu;
    vector<int> sz;

    DSU(int n) {
        dsu.resize(n);
        sz.resize(n);
        iota(dsu.begin(), dsu.end(), 0);
        fill(sz.begin(), sz.end(), 1); 
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
        }
    }

    int get_sz(int x) {
        return sz[find(x)];
    }
};

int n, k;
int adj[MAXN][MAXN];
mi m[MAXN][MAXN];

mi det() {
    mi ans = 1;
    for (int i = 0; i < k; i++) {
        if (m[i][i].v == 0) {
            for (int j = i + 1; j < k; j++) {
                if (m[j][i].v == 0) {
                    swap(m[i], m[j]);
                    ans *= -1;
                    break;
                }
            }

            if (m[i][i].v == 0) {
                return mi(0);
            }
        }

        mi val = m[i][i].v;
        ans *= val;
        for (int j = i; j < k; j++) {
            m[i][j] /= val;
        }

        for (int j = i + 1; j < k; j++) {
            mi first = m[j][i];
            for (int a = 0; a < k; a++) {
                m[j][a] -= m[i][a] * first;
            }
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    DSU dsu(n);
    k = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
            if (j > i && adj[i][j] == 1) {
                if (dsu.find(i) == dsu.find(j)) {
                    cout << "0\n";
                    return 0;
                } else {
                    dsu.join(i, j);
                    k--;
                }
            }
        }
    }

    vector<int> head;
    for (int i = 0; i < n; i++) {
        head.push_back(dsu.find(i));
    }

    sort(head.begin(), head.end());
    head.erase(unique(head.begin(), head.end()), head.end());

    auto lb = [&](int x) { return lower_bound(head.begin(), head.end(), x) - head.begin(); };

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adj[i][j] == -1) {
                int x = lb(dsu.find(i));
                int y = lb(dsu.find(j));

                if (x != y) {
                    m[x][x] += 1;
                    m[y][y] += 1;
                    m[x][y] -= 1;
                    m[y][x] -= 1;
                }
            }
        }
    }

    k--;
    cout << det().v << '\n';

    return 0;
}
