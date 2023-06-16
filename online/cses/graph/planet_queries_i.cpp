// :pray: :steph:
// :pray: :bakekaga:

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
#define MAXN 200000

using namespace std;

int n, q;
int forw[MAXN + 1][31];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> forw[i][0];
    }

    for (int i = 1; i <= 30; i++) {
        for (int j = 1; j <= n; j++) {
            forw[j][i] = forw[forw[j][i - 1]][i - 1];
        }
    }

    while (q--) {
        int x, k; cin >> x >> k;
        for (int i = 30; i >= 0; i--) {
            if ((1 << i) & k) {
                x = forw[x][i];
            }
        }
        cout << x << '\n';
    }
    return 0;
}
