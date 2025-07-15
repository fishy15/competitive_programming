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

void solve() {
    int n;
    cin >> n;

    vector<int> par(n);
    vector<vector<int>> child(n);
    rep(i, 0, n) {
        cin >> par[i];
        par[i]--;
        if (par[i] != -1) {
            child[par[i]].push_back(i);
        }
    }

    // xors stored by layer, and inserted into a set
    vector<int> nimber(n);
    auto dfs = [&](auto &&self, int v) -> pair<deque<int>, set<int>> {
        if (sz(child[v]) == 0) {
            nimber[v] = 1;
            return {{1, 0}, {0, 1}};
        } else if (sz(child[v]) == 1) {
            auto [xor_list, xor_set] = self(self, child[v][0]);

            nimber[v] = nimber[child[v][0]];
            while (xor_set.count(nimber[v])) {
                nimber[v]++;
            }

            xor_list.push_front(nimber[v]);
            xor_set.insert(nimber[v]);
            return {std::move(xor_list), std::move(xor_set)};
        } else {
            deque<int> xor_list;
            for (auto c : child[v]) {
                auto [child_xors, _] = self(self, c);
                if (xor_list.empty()) {
                    xor_list = std::move(child_xors);
                } else {
                    auto nxt_size = min(sz(xor_list), sz(child_xors));
                    xor_list.resize(nxt_size);
                    rep(i, 0, nxt_size) {
                        xor_list[i] ^= child_xors[i];
                    }
                }
            }

            set<int> xor_set(all(xor_list));
            while (xor_set.count(nimber[v])) {
                nimber[v]++;
            }

            xor_list.push_front(nimber[v]);
            xor_set.insert(nimber[v]);
            return {std::move(xor_list), std::move(xor_set)};
        }
    };

    int ans = 0;
    rep(i, 0, n) {
        if (par[i] == -1) {
            dfs(dfs, i);
            ans ^= nimber[i];
        }
    }

    if (ans != 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
