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

string grid[8];
int cur[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
int cnt;

void dfs(int pos) {
    if (pos == 8) {
        set<int> d1, d2;
        for (int i = 0; i < 8; i++) {
            d1.insert(i + cur[i]);
            d2.insert(i - cur[i]);
        }
        cnt += (d1.size() == 8 && d2.size() == 8);
    } else {
        for (int i = 0; i < 8; i++) {
            if (cur[i] == -1 && grid[pos][i] == '.') {
                cur[i] = pos;
                dfs(pos + 1);
                cur[i] = -1;
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i = 0; i < 8; i++) {
        cin >> grid[i];
    }

    dfs(0);

    cout << cnt << '\n';

    return 0;
}
