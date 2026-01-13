#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;

struct DSU {
    vector<int> dsu, size, head;
    DSU(int n) : dsu(n), size(n, 1), head(n) {
        iota(all(dsu), 0);
        iota(all(head), 0);
    }
    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }
    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            int nh = head[y];
            dsu[y] = x;
            size[x] += size[y];
            head[x] = nh;
        }
    }

};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> a(n);
    rep(i, 0, n) {
        cin >> a[i];
        a[i]--;
    }

    int m;
    cin >> m;

    vector<array<int, 2>> events(m);
    rep(i, 0, m) {
        cin >> events[i][0];
        events[i][0]--;
        char typ;
        cin >> typ;
        events[i][1] = "COW"s.find(typ);
    }

    vector<vector<int>> types(n);
    for (auto [x, typ] : events) {
        types[x].push_back(typ);
    }

    DSU dsu(n);
    rep(i, 0, n) {
        if (types[i].empty()) {
            dsu.join(i, a[i]);
        }
    }

    array<int, 3> counts{};
    auto contrib = [&](int idx, int delta) {
        idx = dsu.head[dsu.find(idx)];
        if (!types[idx].empty()) {
            auto typ = types[idx].back();
            counts[typ] += dsu.size[dsu.find(idx)] * delta;
        }
    };

    rep(i, 0, n) {
        if (!types[i].empty()) {
            contrib(i, +1);
        }
    }

    vector<array<int, 3>> results;
    for (int i = m-1; i >= 0; i--) {
        results.push_back(counts);

        auto [idx, _] = events[i];
        contrib(idx, -1);
        if (dsu.find(idx) != dsu.find(a[idx])) {
            contrib(a[idx], -1);
        }

        types[idx].pop_back();
        if (types[idx].empty()) {
            dsu.join(idx, a[idx]);
        }

        contrib(idx, +1);
        if (dsu.find(idx) != dsu.find(a[idx])) {
            contrib(a[idx], +1);
        }
    }

    reverse(all(results));
    for (auto [a, b, c] : results) {
        cout << a << ' ' << b << ' ' << c << '\n';
    }

    return 0;
}
