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
#define MAXN 1000000

using namespace std;

int h, w;
vector<string> grid;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    vector<int> cnt;
    for (int i = 0; i < h; i++) {
        int res = 0;
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 'O') {
                res++;
            }
        }

        cnt.push_back(res);
    }

    for (int i = 0; i < w; i++) {
        int i_cnt = 0;
        for (int j = 0; j < h; j++) {
            if (grid[j][i] == 'J') i_cnt++;
        }
    }

    return 0;
}
