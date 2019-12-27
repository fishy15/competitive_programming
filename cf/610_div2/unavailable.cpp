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
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int q; cin >> q;
    while (q--) {
        int a, b, c, r; cin >> a >> b >> c >> r;
        if (b < a) swap(a, b);
        if (c + r < a || c - r > b) {
            cout << (b - a) << '\n';
        } else if (c - r < a && c + r > b) {
            cout << "0\n";
        } else if (c - r < a) {
            cout << b - (c + r) << '\n';
        } else if (c + r > b) {
            cout << c - r - a << '\n';
        } else {
            cout << b - (c + r) + (c - r) - a << '\n';
        }
    }

    return 0;
}
