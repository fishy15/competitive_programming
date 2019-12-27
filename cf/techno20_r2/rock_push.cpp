// :pray: :steph:
// :pray: :bakekaga:

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
#define MAXN 2000

using namespace std;

int n, m;
vector<string> grid;

int up[MAXN][MAXN];
int left[MAXN][MAXN];

int space_h[MAXN][MAXN];
int space_v[MAXN][MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    up[0][0] = 1;

    for (int i = 0; i < n; i++) {
        int empty = 0;
        for (int j = m - 1; j >= 0; j++) {
            if (grid[i][j] == '.') {
                empty++;
            }
            space_h[i][j] = empty;
        }
    }

    return 0;
}
