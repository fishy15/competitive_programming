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

int dx[] = {2, 1, -1, -2, -2, -1,  1,  2};
int dy[] = {1, 2,  2,  1, -1, -2, -2, -1};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector d(n, vector<int>(n, INF));

    int x1, y1;
    cin >> x1 >> y1;

    int x2, y2;
    cin >> x2 >> y2;

    queue<pair<int, int>> q;
    d[x1][y1] = 0;
    q.push({x1, y1});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
                if (d[nx][ny] == INF) {
                    d[nx][ny] = d[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }

    if (d[x2][y2] == INF) {
        cout << "-1\n";
    } else {
        cout << d[x2][y2] << '\n';
    }

    return 0;
}
