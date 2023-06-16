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

void solve() {
    string s; cin >> s;
    int cur = 0;
    for (char c : s) {
        int i = c - '0';
        for (int j = 0; j < i - cur; j++) {
            cout << '(';
        }
        for (int j = 0; j < cur - i; j++) {
            cout << ')';
        }
        cout << c;
        cur = i;
    }
    for (int i = 0; i < cur; i++) {
        cout << ')';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
