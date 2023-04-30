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

    map<string, int> loc;
    vector<string> ss(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        loc[s] = i;
        ss[i] = s;
    }

    int r;
    cin >> r;

    vector<pair<int, int>> pos(n, {0, 1});
    for (int i = 0; i < r; i++) {
        int m, w;
        cin >> m >> w;
        w--;

        for (int j = 0; j < m; j++) {
            string s;
            cin >> s;
            int p = loc[s];

            if (pos[p].first == w) {
                pos[p].second++;
            } else {
                pos[p] = max(pos[p], {w, 1});
            }
        }
    }

    vector at_d(n, vector<pair<int, int>>());
    for (int i = 0; i < n; i++) {
        auto [d, c] = pos[i];
        at_d[d].push_back({c, i});
    }

    for (auto &v : at_d) {
        sort(v.begin(), v.end(), greater<>());
    }
    
    vector<int> extra;
    for (int i = 0; i < n; i++) {
        if (at_d[i].empty()) {
            cout << ss[extra.back()] << ' ';
            extra.pop_back();
        } else {
            cout << ss[at_d[i][0].second] << ' ';
            for (int j = 1; j < (int) at_d[i].size(); j++) {
                extra.push_back(at_d[i][j].second);
            }
        }
    }

    cout << '\n';

    return 0;
}
