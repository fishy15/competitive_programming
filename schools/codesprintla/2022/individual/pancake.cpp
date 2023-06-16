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

int n, m;
string s;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    cin >> s;

    for (int i = 1; i < n - 2; i++) {
        if (s.substr(i - 1, 3) == "101") s[i] = '1';
    }

    int cur = 0;
    int ans = 0;
    for (char c : s) {
        if (c == '0') {
            if (cur > 0) ans += cur / 2 + 1;
            cur = 0;
        } else {
            cur++;
        }
    }

    if (cur > 0) ans += cur / 2 + 1;
    cout << ans << '\n';

    return 0;
}
