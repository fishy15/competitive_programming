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

// redo

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    char pc = 0;
    int len = 0;
    int ans = 0;
    for (char c : s) {
        if (c == pc) {
            len++;
        } else {
            ans = max(len, ans);
            len = 1;
        }
        pc = c;
    }

    ans = max(len, ans);
    cout << ans + 1 << '\n';
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
