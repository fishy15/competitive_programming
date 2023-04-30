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

void solve() {
    int r, c;
    cin >> r >> c;
    
    vector<string> grid(r);
    int cnt = 0;
    for (int i = 0; i < r; i++) {
        cin >> grid[i];
        cnt += count(grid[i].begin(), grid[i].end(), '^');
    }

    if (r == 1 || c == 1) {
        if (cnt == 0) {
            cout << "Possible\n";
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    cout << '.';
                }
                cout << '\n';
            }
        } else {
            cout << "Impossible\n";
        }
    } else {
        cout << "Possible\n";
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << '^';
            }
            cout << '\n';
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
