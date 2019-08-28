// :pray: :fishy:

#include <iostream>
#include <fstream>
#include <vector>
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
#define MAXN 1000 

using namespace std;

ll arr[MAXN][MAXN];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    ll cur = 0;

    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n / 2; j++) {
            arr[i][j] = cur;
            arr[n - i - 1][j] = cur + 1;
            arr[n - i - 1][n - j - 1] = cur + 2;
            arr[i][n - j - 1] = cur + 3;
            cur += 4;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << ' ';
        }

        cout << '\n';
    }

    /* for (int i = 0; i < n; i++) { */
    /*     int val = 0; */
    /*     for (int j = 0; j < n; j++) { */
    /*         val = val ^ arr[i][j]; */
    /*     } */
    /*     cout << val << '\n'; */
    /* } */

    /* for (int i = 0; i < n; i++) { */
    /*     int val = 0; */
    /*     for (int j = 0; j < n; j++) { */
    /*         val = val ^ arr[j][i]; */
    /*     } */
    /*     cout << val << '\n'; */
    /* } */

    return 0;
}
