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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

void solve() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << "1\n";
        cout << "1\n";
    } else if (n == 2) {
        cout << "2\n";
        cout << "1 2\n";
    } else if (n == 3) {
        cout << "2\n";
        cout << "1 2 2\n";
    } else if (n == 4) {
        cout << "3\n";
        cout << "1 2 2 3\n";
    } else if (n == 5) {
        cout << "3\n";
        cout << "1 2 2 3 3\n";
    } else {
        cout << "4\n";
        rep(i, 1, n+1) {
            if (i % 2 == 0) {
                if (i < (i ^ 2)) {
                    cout << "1 ";
                } else {
                    cout << "2 ";
                }
            } else {
                if (i < (i ^ 2)) {
                    cout << "3 ";
                } else {
                    cout << "4 ";
                }
            }
        }
        cout << '\n';
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
