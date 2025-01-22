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
#include <random>
#include <chrono>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int pos = 0;
    int dir = 1;
    int mini = 0;
    int maxi = 0;
    for (int i = 1; i < n; i++) {
        if (s[i-1] == s[i]) {
            dir *= -1;
        } else {
            pos += dir;
        }
        mini = min(mini, pos);
        maxi = max(maxi, pos);
    }

    cout << maxi - mini + 1 << '\n';
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
