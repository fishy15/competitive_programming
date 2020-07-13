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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n, qq; cin >> n >> qq;
    vector<int> door;
    map<pair<int, int>, int> pos;
    vector<array<pair<int, int>, 17>> up;
    int cnt = 0;

    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        door.push_back(x);
    }

    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        q.push({i, i});
        pos[{i, i}] = cnt++;
        up.push_back({});
    }

    while (!q.empty()) {
        auto tt = q.front();
        q.pop();
        if (tt.first == 0 && tt.second == n - 1) break;
        pair<int, int> opt = {INF, INF};
        if (tt.first > 0) {
            opt = min(opt, {door[tt.first - 1], 0});
        }
        if (tt.second < n - 1) {
            opt = min(opt, {door[tt.second], 1});
        }

        if (!opt.second) {
            pair<int, int> nxt = {tt.first - 1, tt.second};
            if (!pos.count(nxt)) {
                pos[nxt] = cnt++;
                up.push_back({});
                q.push(nxt);
            }
            up[pos[tt]][0] = {pos[nxt], tt.first - 1};
        } else {
            pair<int, int> nxt = {tt.first, tt.second + 1};
            if (!pos.count(nxt)) {
                pos[nxt] = cnt++;
                up.push_back({});
                q.push(nxt);
            }
            up[pos[tt]][0] = {pos[nxt], tt.second + 1};
        }
        pos.erase(pos.find(tt));
    }

    for (int i = 1; i < 17; i++) {
        for (int j = 0; j < up.size(); j++) {
            up[j][i] = up[up[j][i - 1].first][i - 1];
        }
    }

    while (qq--) {
        int a, b; cin >> a >> b;
        a--; b--;
        pair<int, int> cur = {a, a};
        for (int i = 0; i < 17; i++) {
            if ((1 << i) & b) cur = up[cur.first][i];
        }
        cout << cur.second + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
