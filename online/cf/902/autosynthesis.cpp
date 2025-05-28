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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> nxt(n);
    rep(i, 0, n) {
        cin >> nxt[i];
        nxt[i]--;
    }

    vector<int> indeg(n);
    rep(i, 0, n) {
        indeg[nxt[i]]++;
    }

    // -1 = unset, 0 = uncircled, 1 = circled
    vector<int> state(n, -1);
    bool valid = true;

    auto mark_uncircled = [&](auto &&mu, auto &&mc, int v) -> void {
        if (state[v] == -1) {
            state[v] = 0;
            mc(mu, mc, nxt[v]);
        } else {
            valid &= state[v] == 0;
        }
    };

    auto mark_circled = [&](auto &&mu, auto &&mc, int v) -> void {
        if (state[v] == -1) {
            state[v] = 1;
            indeg[nxt[v]]--;
            if (indeg[nxt[v]] == 0) {
                mu(mu, mc, nxt[v]);
            }
        } else {
            valid &= state[v] == 1;
        }
    };

    rep(i, 0, n) {
        if (state[i] == -1 && indeg[i] == 0) {
            mark_uncircled(mark_uncircled, mark_circled, i);
        }
    }

    // resolve cycles
    rep(i, 0, n) {
        if (state[i] == -1) {
            mark_uncircled(mark_uncircled, mark_circled, i);
        }
    }

    if (valid) {
        vector<int> ans;
        rep(i, 0, n) {
            if (state[i] == 0) {
                ans.push_back(nxt[i]);
            }
        }

        cout << sz(ans) << '\n';
        for (auto x : ans) {
            cout << x+1 << ' ';
        }
        cout << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}
