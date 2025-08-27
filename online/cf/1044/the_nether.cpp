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

template<typename T>
int ask(int x, const T &locs) {
    cout << "? ";
    cout << x+1 << ' ';
    cout << sz(locs) << ' ';
    for (auto a : locs) cout << a+1 << ' ';
    cout << endl;

    int res;
    cin >> res;

    if (res == -1) {
        exit(0);
    }

    return res;
}

void answer(const vector<int> &locs) {
    cout << "! ";
    cout << sz(locs) << ' ';
    for (auto a : locs) cout << a+1 << ' ';
    cout << endl;
}

void solve() {
    int n;
    cin >> n;

    vector<int> full(n);
    iota(all(full), 0);

    pair<int, int> best{-1, -1};
    vector<int> len_at(n);
    rep(i, 0, n) {
        auto len = ask(i, full);
        len_at[i] = len;
        best = max(best, pair{len, i});
    }

    auto len = best.first;
    auto x = best.second;

    set<int> present{all(full)};
    vector<int> path = {x};

    rep(i, 0, n) {
        if (i != x) {
            present.erase(i);
            auto new_len = ask(x, present);
            if (new_len != len) {
                present.insert(i);
                path.push_back(i);
            }
        }
    }

    sort(all(path), [&](int a, int b) { return len_at[a] > len_at[b]; });
    answer(path);
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
