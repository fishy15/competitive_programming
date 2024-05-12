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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ans = 0;
    auto dfs = [&](auto &&self, int v, int p) -> deque<int> {
        auto it = find(adj[v].begin(), adj[v].end(), p);
        if (it != adj[v].end()) {
            adj[v].erase(it);
        }

        deque<int> cnts;
        switch (adj[v].size()) {
            case 0:
                cnts = {1};
                break;
            case 1:
                cnts = self(self, adj[v][0], v);
                while (cnts.size() > 1) {
                    ans += cnts.back();
                    cnts.pop_back();
                }
                cnts.push_front(1);
                break;
            default:
                auto cnts1 = self(self, adj[v][0], v);
                auto cnts2 = self(self, adj[v][1], v);

                if (cnts1.size() < cnts2.size()) swap(cnts1, cnts2);

                while (cnts1.size() > cnts2.size() + 1) {
                    ans += cnts1.back();
                    cnts1.pop_back();
                }

                for (int i = 0; i < (int) cnts2.size(); i++) {
                    cnts1[i] += cnts2[i];
                }
                cnts1.push_front(1);

                cnts = std::move(cnts1);
        }

        return cnts;
    };

    dfs(dfs, 0, 0);

    cout << ans << '\n';

    return 0;
}
