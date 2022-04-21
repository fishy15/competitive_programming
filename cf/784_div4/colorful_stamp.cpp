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

bool check(string s) {
    if (s.empty()) return true;

    int sz = s.size();
    for (int i = 0; i < sz - 1; i++) {
        if (s[i] != s[i + 1]) {
            return true;
        }
    }

    return false;
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    string cur = "";
    for (char c : s) {
        if (c == 'W') {
            if (!check(cur)) {
                cout << "NO\n";
                return;
            }

            cur = "";
        } else {
            cur += c;
        }
    }

    if (!check(cur)) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
