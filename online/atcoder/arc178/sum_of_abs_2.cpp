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
#define MAXA 200000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, l;
    cin >> n >> l;

    vector<int> qry(n);
    for (auto &x : qry) {
        cin >> x;
    }

    vector<int> min_moves(MAXA+1, INF);
    min_moves[0] = 0;

    int cur = 0;
    for (int i = l-1; i >= 1; i -= 2) {
        cur += i;
        if (cur > MAXA) {
            break;
        }

        for (int j = cur; j <= MAXA; j++) {
            min_moves[j] = min(min_moves[j - cur] + 1, min_moves[j]);
        }
    }

    for (auto x : qry) {
        if (min_moves[x] == INF) {
            cout << "-1\n";
        } else {
            cout << min_moves[x] << '\n';
        }
    }

    return 0;
}
