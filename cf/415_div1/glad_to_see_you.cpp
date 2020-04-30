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
#define MAXN 100000

using namespace std;

int n, k;

int find(int x, int y) {
    int l = x;
    int r = y;

    while (l <= r) {
        if (l == r) {
            return l;
        }
        int m = l + (r - l) / 2;
        cout << "1 " << m << ' ' << m + 1 << '\n';
        cout.flush();
        string res; cin >> res;
        if (res == "TAK") {
            r = m;
        } else {
            l = m + 1;
        }
    }

    return l;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    int p1 = find(1, n);
    int p2 = p1 == 1 ? 2 : find(1, p1 - 1);
    cout << 1 << ' ' << p2 << ' ' << p1 << '\n';
    cout.flush();
    string res; cin >> res;
    if (res != "TAK") {
        p2 = find(p1 + 1, n);
    }

    cout << 2 << ' ' << p1 << ' ' << p2 << '\n';

    return 0;
}
