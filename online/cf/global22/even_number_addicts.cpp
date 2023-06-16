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
    int n;
    cin >> n;

    int odd = 0;
    int even = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (x % 2 == 0) {
            even++;
        } else {
            odd++;
        }
    }

    // whoever moves can guarantee win
    vector<vector<array<bool, 2>>> wins(odd + 1, vector<array<bool, 2>>(even + 1, {false, false}));

    if (n % 2 == 0) {
        // ends on alice turn, want 0 sum
        wins[0][0][0] = true;
    } else {
        // ends on bob turn, want what makes alice sum 1
        wins[0][0][1 - odd % 2] = true;
    }

    for (int o = 0; o <= odd; o++) {
        for (int e = 0; e <= even; e++) {
            for (int x = 0; x < 2; x++) {
                if (o > 0) {
                    int po = o - 1;
                    int pe = e;
                    int px = ((odd + o) + x) % 2;
                    // (odd - o) % 2 => how many odds taken so far % 2
                    // ((odd - o) - x) % 2 => how many odds taken by other person % 2

                    wins[o][e][x] |= !wins[po][pe][px];
                }

                if (e > 0) {
                    int po = o;
                    int pe = e - 1;
                    int px = ((odd + o) + x) % 2;

                    wins[o][e][x] |= !wins[po][pe][px];
                }
            }
        }
    }

    if (wins[odd][even][0]) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
