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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n;
vector<pair<int, int>> pts;

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        pts.push_back({x, y});
    }
    
    while (true) {
        array<vector<int>, 4> loc;

        for (int i = 0; i < n; i++) {
            int pos = (abs(pts[i].first) % 2) * 2 + abs(pts[i].second) % 2;
            loc[pos].push_back(i);
        }

        int mm = 0;
        for (auto &v : loc) mm = max(mm, (int)v.size());
        if (mm == n) {
            for (int i = 0; i < n; i++) {
                if (pts[i].first % 2) pts[i].first++;
                if (pts[i].second % 2) pts[i].second++;
                pts[i].first /= 2;
                pts[i].second /= 2;
            }
            continue;
        } 

        if (loc[0].size() + loc[3].size() == n) {
            cout << loc[0].size() << '\n';
            for (int i : loc[0]) cout << i + 1 << ' ';
            cout << '\n';
        } else if (loc[1].size() + loc[2].size() == n) {
            cout << loc[1].size() << '\n';
            for (int i : loc[1]) cout << i + 1 << ' ';
            cout << '\n';
        } else {
            cout << loc[0].size() + loc[3].size() << '\n';
            for (int i : loc[0]) cout << i + 1 << ' ';
            for (int i : loc[3]) cout << i + 1 << ' ';
            cout << '\n';
        }
        return 0;
    }

    return 0;
}
