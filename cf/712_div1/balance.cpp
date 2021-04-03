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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

bool check(const string &s) {
    int cur = 0;
    for (char c : s) {
        if (c == '(') {
            cur++;
        } else {
            cur--;
        }

        if (cur < 0) {
            return false;
        }
    }

    return cur == 0;
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    string a, b;

    int one = 0;
    for (char c : s) {
        if (c == '1') {
            one++;
        }
    }

    if (one % 2 == 1 || (n - one) % 2 == 1) {
        cout << "NO\n";
        return;
    }

    int cur_one = 0;
    int cur_zero = 0;
    for (char c : s) {
        if (c == '1') {
            cur_one++;
            if (cur_one <= one / 2) {
                a += '(';
                b += '(';
            } else {
                a += ')';
                b += ')';
            }
        } else {
            cur_zero++;
            if (cur_zero % 2 == 1) {
                a += '(';
                b += ')';
            } else {
                a += ')';
                b += '(';
            }
        }
    }

    if (check(a) && check(b)) {
        cout << "YES\n";
        cout << a << '\n';
        cout << b << '\n';
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
