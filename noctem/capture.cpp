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
#define MAXN 2000

using namespace std;

int n, r, c, a, b;
vector<pair<int, int>> loc;
int vis[MAXN][MAXN];
int dist[MAXN][MAXN];

int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};

int range[MAXN][MAXN];

bool ok(int x, int y) {
    return x >= 0 && y >= 0 && x < r && y < c && !vis[x][y];
}

int main() {
    ifstream fin("capture.in");
    ofstream fout("capture.out");

    fin >> n >> r >> c >> a >> b;
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        int a, b; fin >> a >> b;
        loc.push_back({a, b});
        q.push({a, b});
        vis[a][b] = true;
    }

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            if (ok(x + dx[i], y + dy[i])) {
                vis[x + dx[i]][y + dy[i]] = true;
                dist[x + dx[i]][y + dy[i]] = dist[x][y] + 1;
                q.push({x + dx[i], y + dy[i]});
            }
        }
    }

    for (int i = 0; i < c; i++) {
        multiset<int> cur;
        // init
        for (int j = 0; j < a; j++) {
            cur.insert(dist[j][i]);
        }
        range[0][i] = *cur.begin();
        for (int j = a; j < r; j++) {
            cur.erase(cur.find(dist[j - a][i]));
            cur.insert(dist[j][i]);
            range[j - a + 1][i] = *cur.begin();
        }
    }

    int ans = 0;
    for (int i = 0; i < r; i++) {
        /* cout << i << '\n'; */
        multiset<int> cur;
        // init
        for (int j = 0; j < b; j++) {
            cur.insert(range[i][j]);
        }

        ans = max(ans, *cur.begin());
        for (int j = b; j < c; j++) {
            cur.erase(cur.find(range[i][j - b]));
            cur.insert(range[i][j]);
            ans = max(ans, *cur.begin());
        }
    }

    fout << ans << '\n';

    return 0;
}
