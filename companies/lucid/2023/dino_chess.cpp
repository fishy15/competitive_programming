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

    int m, n;
    cin >> m >> n;

    int ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int num_cols = n / m + (i < n % m);
            int num_rows = n / m + (j < n % m);

            if (num_cols % 2 == 1) num_cols++;
            if (num_rows % 2 == 1) num_rows++;

            ans += num_cols / 2 * num_rows / 2;
        }
    }

    cout << ans << '\n';

    return 0;
}
