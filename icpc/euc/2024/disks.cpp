#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct circ {
    ll x, y, r;

    bool tangent(const circ &other) const {
        auto dx = x - other.x;
        auto dy = y - other.y;
        return dx*dx + dy*dy == (r + other.r) * (r + other.r);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<circ> circles(n);
    rep(i, 0, n) {
        auto &c = circles[i];
        cin >> c.x >> c.y >> c.r;
    }

    vector<vector<int>> adj(n);
    rep(i, 0, n) {
        rep(j, i+1, n) {
            if (circles[i].tangent(circles[j])) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    // 0 = unvisited, 1 = color 1, 2 = color 2
    vector<int> color(n);

    auto dfs = [&](auto &&self, int v, int c, int &one, int &two) -> bool {
        if (color[v] == 0) {
            color[v] = c;
            if (c == 1) {
                one++;
            } else {
                two++;
            }

            bool flag = true;
            for (auto e : adj[v]) {
                auto ok = self(self, e, 3 - c, one, two);
                if (!ok) {
                    flag = false;
                }
            }
            return flag;
        } else {
            return color[v] == c;
        }
    };

    rep(i, 0, n) {
        if (color[i] == 0) {
            int one = 0;
            int two = 0;
            auto ok = dfs(dfs, i, 1, one, two);
            if (ok && one != two) {
                cout << "YES\n";
                return 0;
            }
        }
    }

    cout << "NO\n";

    return 0;
}

