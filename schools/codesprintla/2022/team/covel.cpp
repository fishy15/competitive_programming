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
#include <chrono>
#include <random>
#include <cassert>

#include <ext/pb_ds/assoc_container.hpp>

#define ll long long
#define ld long double
#define eps 1e-8

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000
#define NDEBUG

using namespace std;
using namespace __gnu_pbds;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MOD = 1e9+7;

int getRand(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

int add(int a, int b) {
    assert(a < MOD);
    assert(b < MOD);
    assert(a < MOD && b < MOD);
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int mul(int a, int b) { 
    assert(a >= 0);
    assert(b >= 0);
    assert(a < MOD && b < MOD && a >= 0 && b >= 0);
    assert((1LL * a * b) % MOD < MOD);
    return (1LL * a * b) % MOD; }

int binpow(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    assert(res < MOD);
    return res;
}

int sub(int a, int b) { if (b == 0) return a; assert(a < MOD && b < MOD); assert(a >= 0); assert(b >= 0); assert(MOD - b < MOD); return add(a, MOD - b); }

struct Hash
{
    // All 1-indexed
    int baseCnt, maxLen, cur = 0;
    vector<vector<int>> bases, inverse;
    vector<vector<vector<int>>> hashVal;
    Hash(int baseCnt, int maxLen) : baseCnt(baseCnt), maxLen(maxLen), bases(baseCnt, vector<int>(maxLen + 1)), inverse(baseCnt, vector<int>(maxLen + 1)) {
        for (int i = 0; i < baseCnt; ++i) {
            bases[i][0] = 1;
            bases[i][1] = getRand(10000, 200000);
            inverse[i][0] = 1;
            inverse[i][1] = binpow(bases[i][1], MOD - 2);
            for (int j = 2; j <= maxLen; ++j) {
                assert(bases[i][1] >= 0);
                assert(inverse[i][1] >= 0);
                bases[i][j] = mul(bases[i][j - 1], bases[i][1]);
                inverse[i][j] = mul(inverse[i][j - 1], inverse[i][1]);
            }
        }
        hashVal.push_back({{}});
    }
    void addString(string& s) {
        int n = s.size();
        ++cur;
        hashVal.push_back(vector<vector<int>>(baseCnt, vector<int>(n + 1)));
        for (int i = 0; i < baseCnt; ++i)
            for (int j = 0; j < n; ++j) {
                hashVal[cur][i][j + 1] = add(hashVal[cur][i][j], mul(bases[i][j], s[j] - '$' + 1));
            }
    }
    int calcVal(int id, int base, int l, int r) {
        return mul(sub(hashVal[id][base][r], hashVal[id][base][l - 1]), inverse[base][l - 1]);
    }
    bool isEqual(int id1, int l1, int r1, int id2, int l2, int r2) {
        for (int i = 0; i < baseCnt; ++i)
            if (calcVal(id1, i, l1, r1) != calcVal(id2, i, l2, r2))
                return false;
        return true;
    }
};

Hash h(2, 3000);
pair<int, int> qq[3000][3000];

struct phash {
    int operator()(pair<int, int> p) const {
        return p.first ^ p.second;
    }
};

bool check(int n, int m, int k) {
    gp_hash_table<pair<int, int>, int, phash> cnt;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            qq[i][j].first = h.calcVal(i + 1, 0, j + 1, j + k);
            qq[i][j].second = h.calcVal(i + 1, 1, j + 1, j + k);
            cnt[qq[i][j]]++;
        }
    }

    int ok = 0;
    for (int i = 0; i < 1; i++) {
        gp_hash_table<pair<int, int>, int, phash> cur;

        for (int j = 0; j < n; j++) {
            cur[qq[i][j]]++;
        }

        for (auto [hash, c] : cur) {
            if (cnt[hash] == c) {
                ok += c;
            }
        }
    }

    return 2 * ok >= n;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    vector<string> songs;

    for (int i = 0; i < m; i++) {
        string s; cin >> s;
        s += string(n - 1, '$');
        songs.push_back(s);
        h.addString(s);
    }

    int l = 1;
    int r = n;
    int a = -1;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(n, m, mid)) {
            a = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << a << '\n';

    return 0;
}
