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

bool is_palindrome(string s) {
    auto rev = s;
    reverse(rev.begin(), rev.end());
    return s == rev;
}

void solve() {
    string s;
    cin >> s;

    int sz = s.size();

    bool all_same = true;
    for (int i = 1; i < sz; i++) {
        all_same &= (s[0] == s[i]);
    }

    if (all_same) {
        cout << "-1\n";
    } else if (is_palindrome(s)) {
        cout << sz - 1 << '\n';
    } else {
        cout << sz << '\n';
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
