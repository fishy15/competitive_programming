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

    int n, k;
    cin >> n >> k;
    
    vector vis(n, vector(n, -1));

    int sunk_cnt = 0;
    auto shoot = [&](int i, int j) {
        if (vis[i][j] == -1) {
            cout << i+1 << ' ' << j+1 << endl;

            string res;
            cin >> res;

            if (res == "sunk") {
                sunk_cnt++;
                if (sunk_cnt == k) {
                    // we won
                    exit(0);
                }
            }
            
            return vis[i][j] = res == "miss" ? 0 : 1;
        }

        return vis[i][j];
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i % 5 == j % 5) {
                if (shoot(i, j) == 1) {
                    for (int k = 1; k <= 4; k++) {
                        if (i-k >= 0) shoot(i-k, j);
                        if (j-k >= 0) shoot(i, j-k);
                        if (i+k < n) shoot(i+k, j);
                        if (j+k < n) shoot(i, j+k);
                    }
                }
            }
        }
    }

    return 0;
}
