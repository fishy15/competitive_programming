// :pray: :fishy:

#include <iostream>
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
#define MAXN 500000

using namespace std;

int arr[MAXN + 1];
int sum[700][700];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int q; cin >> q;
    while (q--) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 1) {
            arr[x] += y;
            for (int i = 1; i < 700; i++) {
                sum[i][x % i] += y;
            }
        } else {
            if (x < 700) {
                cout << sum[x][y] << '\n';
            } else {
                int s = 0;
                for (int i = y; i <= MAXN; i += x) {
                    s += arr[i];
                }
                cout << s << '\n';
            }
        }
    }

    return 0;
}
