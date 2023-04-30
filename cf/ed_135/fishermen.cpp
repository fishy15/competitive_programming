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
#define MAXN 1000000

using namespace std;

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> ppl(n);
    vector<int> locations;

    for (int i = 0; i < n; i++) {
        cin >> ppl[i];
        for (int j = 1; j <= n; j++) {
            locations.push_back(j * ppl[i]);
        }
    }

    sort(locations.begin(), locations.end());
    locations.erase(unique(locations.begin(), locations.end()), locations.end());

    auto get = [&](int l) {
        return lower_bound(locations.begin(), locations.end(), l) - locations.begin();
    };

    vector<vector<int>> adj(locations.size() + ppl.size());
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[get(j * ppl[i])].push_back(locations.size() + i);
        }
    }

    vector<int> match(adj.size(), -1);
    vector<bool> vis(adj.size());

    auto dfs = y_combinator([&](auto self, int v) {
        
    });

    for (int i = 0; i < (int) locations.size(); i++) {
        
    }

    return 0;
}
