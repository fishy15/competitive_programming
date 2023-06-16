/*
 * (i, j) must have be a J, and there must be at least one O in the row to the right and at least one I 
 * in the column below. In fact, the number of combinations that include this J is (# of O's to the right) * (# of I's below). We can use prefix sums to calculate these values for each J value and then take the 
 * product of each.
 */

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
#define MAXN 3010

using namespace std;

int h, w;
string grid[MAXN];

ll ans;
int ocnt[MAXN][MAXN];
int icnt[MAXN][MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        cin >> grid[i];
    }

    for (int i = 0; i < h; i++) {
        for (int j = w - 1; j >= 0; j--) {
            ocnt[i][j] = ocnt[i][j + 1];
            if (grid[i][j] == 'O') ocnt[i][j]++;
        }
    }

    for (int j = 0; j < w; j++) {
        for (int i = h - 1; i >= 0; i--) {
            icnt[i][j] = icnt[i + 1][j];
            if (grid[i][j] == 'I') icnt[i][j]++;
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 'J') {
                ans += (ll) ocnt[i][j] * icnt[i][j];
            }
        }
    }
    
    cout << ans << '\n';

    return 0;
}
