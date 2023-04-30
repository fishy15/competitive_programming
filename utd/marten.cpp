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


// a->b (*a).b

int n;
vector<string> tot;
set<string> suffix;
vector<string> all_str;
vector<tuple<string, string, bool>> statement;

map<string, vector<int>> match;

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        string a, b, c; cin >> a >> b >> c;

        if ((int) a.size() > 3) a = a.substr(a.size() - 3, 3);
        if ((int) c.size() > 3) c = c.substr(c.size() - 3, 3);

        suffix.insert(a);
        suffix.insert(c);
        statement.push_back({a, c, b == "is"});
        all_str.push_back(a);
        all_str.push_back(c);
    }

    sort(all_str.begin(), all_str.end());
    auto lb = [&](const string &s) { 
        return lower_bound(all_str.begin(), all_str.end(), s) - all_str.begin();
    };

    DSU dsu(2 * n);
    vector<pair<int, int>> check;
    for (auto [a, b, same] : statement) {
        int i = lb(a);
        int j = lb(b);

        if ((int) a.size() == 3) {
            if (suffix.count(a.substr(2, 1))) {
                a = a.substr(2, 1);
            } else if (suffix.count(a.substr(1, 2))) {
                a = a.substr(1, 2);
            } 
        } else if ((int) a.size() == 2) {
            if (suffix.count(a.substr(1, 1))) {
                a = a.substr(1, 1);
            }
        }

        if ((int) b.size() == 3) {
            if (suffix.count(b.substr(2, 1))) {
                b = b.substr(2, 1);
            } else if (suffix.count(b.substr(1, 2))) {
                b = b.substr(1, 2);
            } 
        } else if ((int) b.size() == 2) {
            if (suffix.count(b.substr(1, 1))) {
                b = b.substr(1, 1);
            }
        }

        match[a].push_back(i);
        match[b].push_back(j);

        if (same) {
            dsu.join(i, j);
        } else {
            check.push_back({i, j});
        }
    }
    
    for (auto &[suffix, v] : match) {
        for (int k = 0; k < (int) v.size() - 1; k++) {
            int i = v[k];
            int j = v[k + 1];

            dsu.join(i, j);
        }
    }

    for (auto [a, b] : check) {
        if (dsu.find(a) == dsu.find(b)) {
            cout << "wait what?\n";
            return 0;
        }
    }

    cout << "yes\n";

    return 0;
}
