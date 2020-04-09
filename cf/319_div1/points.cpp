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
vector<pair<int, int>> points[1001];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        points[x / 1000].push_back({y, i + 1});
    }

    for (int i = 0; i < 1000; i++) {
        sort(points[i].begin(), points[i].end());
    }

    bool top = true;

    for (int i = 0; i < 1000; i++) {
        if (!points[i].empty()) {
            if (top) {
                for (int j = 0; j < points[i].size(); j++) {
                    cout << points[i][j].second << ' ';
                }
            } else {
                for (int j = points[i].size() - 1; j >= 0; j--) {
                    cout << points[i][j].second << ' ';
                }
            }

            top = !top;
        }
    }

    cout << '\n';

    return 0;
}
