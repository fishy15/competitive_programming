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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

constexpr ll INFLL = 1e18;

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

void floyd_warshall(vector<vector<ll>> &d) {
    int n = sz(d);
    rep(k, 0, n) {
        rep(i, 0, n) {
            rep(j, 0, n) {
                ckmin(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<array<int, 4>> edges(m);
    for (auto &[a, b, c, d] : edges) {
        cin >> a >> b >> c >> d;
        a--;
        b--;
    }

    vector zero(n, vector(n, INFLL));
    vector one(n, vector(n, INFLL));

    auto zero_diag = [&](vector<vector<ll>> &v) {
        rep(i, 0, n) {
            v[i][i] = 0;
        }
    };

    zero_diag(zero);
    zero_diag(one);

    for (auto [a, b, c, d] : edges) {
        ckmin(zero[a][b], (ll) c);
        if (d > 0) {
            ckmin(one[a][b], (ll) c);
        }
    }

    floyd_warshall(zero);
    floyd_warshall(one);

    vector two(n, vector(n, INFLL));
    zero_diag(two);
    for (auto [a, b, c, d] : edges) {
        if (d > 1) {
            ckmin(two[a][b], (ll) c);
        }
    }
    rep(i, 0, n) {
        rep(j, 0, n) {
            auto c = one[i][j] + zero[j][i] + one[i][j];
            ckmin(two[i][j], c);
        }
    }

    floyd_warshall(two);

    rep(i, 0, n) {
        rep(j, 0, n) {
            if (two[i][j] == INFLL) {
                cout << "-1 ";
            } else {
                cout << two[i][j] << ' ';
            }
        }
        cout << '\n';
    }

    return 0;
}
