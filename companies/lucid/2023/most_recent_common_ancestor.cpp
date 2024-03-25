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
#include <sstream>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    map<string, vector<string>> child;
    map<string, string> parent;

    string trash;
    getline(cin, trash);

    for (int i = 0; i < n; i++) {
        string edge;
        getline(cin, edge);

        int sz = edge.size();
        auto loc = edge.find("--");
        auto a = edge.substr(0, loc - 1);
        auto b = edge.substr(loc + 3, sz - (loc + 3) + 1);

        child[a].push_back(b);
        parent[b] = a;
    }

    map<string, int> d;

    auto get_dp = [&](auto self, string s) -> int {
        if (!d.count(s)) {
            int ans;
            if (parent.count(s)) {
                ans = self(self, parent[s]) + 1;
            } else {
                ans = 0;
            }
            return d[s] = ans;
        }
        return d[s];
    };

    auto get_d = [get_dp](string s) { return get_dp(get_dp, s); };

    string a, b;
    getline(cin, a);
    getline(cin, b);

    while (a != b) {
        if (get_d(a) > get_d(b)) {
            a = parent[a];
        } else {
            b = parent[b];
        }
    }

    cout << a << '\n';

    return 0;
}
