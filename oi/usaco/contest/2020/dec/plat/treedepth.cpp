/*
 * First, we note that for a given permutation, the depth of node i is the number of suffix mins in [0, i]
 * + number of prefix mins in [i, n - 1] + 1 (ignoring i in the prefix/suffix mins). Therefore, we need to 
 * be able to quickly calculate the number of permutations where the prefix/suffix min changes at location 
 * j. Using generating functions, we can let a_k * x^k be the term for a_k permutations with k inversions. 
 * The first element contributes 0 inversions, the second contributes 0 or 1 inversions, etc., so the
 * generating function is 1 * (1 + x) * (1 + x + x^2) * .... However, if we want the index at j to 
 * contribute to the depth, then either it contributes 0 inversions in the interval [j, i] (if j < i) or
 * j - i inversions in the interval [i, j] (if j > i). In either case, we just need to divide the 
 * generating function for the total number of inversions by the appropriate polynomial and then get the 
 * coefficient from the appropriate term.
 */

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

int n, k, mod = 2;

struct mi {
    int v;
    mi() : v(0) {}
    mi(ll v) : v(v % mod) {}
    mi &operator+=(const mi &m) {
        v += m.v;
        if (v >= mod) v -= mod;
        return *this;
    }
    mi &operator-=(const mi &m) {
        v -= m.v;
        if (v < 0) v += mod;
        return *this;
    }
    mi &operator*=(const mi &m) {
        v = (ll) v * m.v % mod;
        return *this;
    }
    mi operator+(const mi &m) const { 
        mi m2(v);
        return m2 += m;
    }
    mi operator-(const mi &m) const {
        mi m2(v);
        return m2 -= m;
    }
    mi operator*(const mi &m) const {
        mi m2(v);
        return m2 *= m;
    }
    mi &operator=(const mi &m) {
        v = m.v;
        return *this;
    }
};

vector<mi> mul(vector<mi> &cur, int p) {
    vector<mi> res(cur.size() + p);
    int csz = (int)(cur.size());
    int rsz = (int)(res.size());
    for (int i = 0; i < csz; i++) {
        res[i] += cur[i];
        if (i + p + 1 < rsz) res[i + p + 1] -= cur[i];
    }
    for (int i = 1; i < rsz; i++) {
        res[i] += res[i - 1];
    }
    return res;
}

vector<mi> div(vector<mi> &cur, int p) {
    vector<mi> res(cur.size() - p);
    int rsz = (int)(res.size());
    res[0] = cur[0];
    for (int i = 1; i < rsz; i++) {
        res[i] = cur[i] - cur[i - 1];
    }
    for (int i = 0; i < rsz; i++) {
        if (i + p + 1 < rsz) res[i + p + 1] += res[i];
    }
    return res;
}

mi ans[310];
vector<mi> tot = {mi(1)};

int main() {
    ifstream fin("treedepth.in");
    ofstream fout("treedepth.out");

    fin >> n >> k >> mod;

    for (int i = 0; i < n; i++) {
        tot = mul(tot, i);
    }

    for (int sz = 1; sz < n; sz++) {
        auto poly = div(tot, sz);
        int psz = poly.size();

        // left side
        if (k < psz) {
            for (int i = sz; i < n; i++) {
                ans[i] += poly[k];
            }
        }

        // right side
        if (k >= sz && k - sz < psz) {
            for (int i = 0; i < n - sz; i++) {
                ans[i] += poly[k - sz];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        ans[i] += tot[k];
    }

    for (int i = 0; i < n; i++) {
        fout << ans[i].v;
        if (i < n - 1) {
            fout << ' ';
        } else {
            fout << '\n';
        }
    }

    return 0;
}

