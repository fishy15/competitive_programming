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

int get_mov(vector<array<int, 30>> &path, int start, int k) {
    for (int i = 0; i < 30; i++) {
        if (k & (1 << i)) {
            start = path[start][i];
        }
    }
    return start;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<array<int, 30>> left(n);
    vector<array<int, 30>> right(n);

    for (int i = 0; i < n; i++) {
        cin >> left[i][0] >> right[i][0];
        left[i][0]--;
        right[i][0]--;
    }

    for (int j = 1; j < 30; j++) {
        for (int i = 0; i < n; i++) {
            left[i][j] = left[left[i][j - 1]][j - 1];
            right[i][j] = right[right[i][j - 1]][j - 1];
        }
    }

    int q;
    cin >> q;

    while (q--) {
        ll x, k;
        cin >> x >> k;
        x--;

        x = get_mov(left, x, k);
        x = get_mov(right, x, k);
        x = get_mov(left, x, k);
        x = get_mov(right, x, k);

        cout << x + 1 << '\n';
    }

    return 0;
}
