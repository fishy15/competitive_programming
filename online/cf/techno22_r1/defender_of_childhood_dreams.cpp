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

    int n, k;
    cin >> n >> k;

    vector edges(n, vector<int>(n, -1));

    vector<vector<int>> groups;
    rep(i, 0, n) {
        groups.push_back({i});
    }

    int cur_c = 1;
    while (sz(groups) > 1) {
        vector<vector<int>> nxt;
        rep(i, 0, sz(groups)) {
            int nxt_group = i / k;
            if (nxt_group >= sz(nxt)) {
                nxt.push_back({});
            }

            for (auto x : nxt[nxt_group]) {
                for (auto y : groups[i]) {
                    edges[x][y] = cur_c;
                }
            }
            nxt[nxt_group].insert(end(nxt[nxt_group]), all(groups[i]));
        }

        cur_c++;
        groups = nxt;
    }

    cout << cur_c - 1 << '\n';
    rep(i, 0, n) {
        rep(j, i+1, n) {
            cout << edges[i][j] << ' ';
        }
    }
    cout << '\n';

    return 0;
}
