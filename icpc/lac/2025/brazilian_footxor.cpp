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
#include <bitset>
#include <cassert>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

constexpr int BITS = 1501;

array<int, BITS> ident;
array<bitset<BITS>, BITS> basis;
array<bitset<BITS>, BITS> used;

vector<int> add(bitset<BITS> val, int idx) {
    bitset<BITS> cur_used;
    cur_used[idx] = 1;
    rep(i, 0, BITS) {
        if (val[i]) {
            if (ident[i] != -1) {
                val ^= basis[i];
                cur_used ^= used[i];
            } else {
                basis[i] = val;
                ident[i] = idx;
                used[i] = cur_used;
                return {};
            }
        }
    }

    vector<int> res;
    rep(i, 0, BITS) {
        if (cur_used[i]) {
            res.push_back(i);
        }
    }
    return res;
}

bitset<BITS> read(int k) {
    string s;
    cin >> s;
    reverse(all(s));

    bitset<BITS> b;
    rep(i, 0, k) {
        b[i] = (s[i] == '1'); 
    }
    b[k] = 1;
    return b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ident.fill(-1);

    int n, k;
    cin >> n >> k;

    rep(i, 0, n) {
        auto b = read(k);
        auto v = add(b, i);
        if (!v.empty()) {
            vector<int> ans(n);
            rep(i, 0, sz(v) / 2) {
                ans[v[i]] = 1;
            }
            rep(i, sz(v) / 2, sz(v)) {
                ans[v[i]] = 2;
            }

            rep(i, 0, n) {
                cout << ans[i];
            }
            cout << '\n';
            return 0;
        }
    }

    cout << "*\n";
    return 0;
}
