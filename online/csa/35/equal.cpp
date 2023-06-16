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
#define MAXN 1010

using namespace std;

int n;
int mat[MAXN][MAXN];
int row[MAXN];
int col[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
            row[i] += mat[i][j];
            col[j] += mat[i][j];
        }
    }

    int x = max(*max_element(row, row + n), *max_element(col, col + n));

    for (int i = 0; i < n; i++) {
        row[i] = x - row[i];
        col[i] = x - col[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int m = min(row[i], col[j]);
            row[i] -= m;
            col[j] -= m;
            mat[i][j] += m;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mat[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
