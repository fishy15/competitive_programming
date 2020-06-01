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
    int n;
    string s; cin >> s;
    n = (int)(s.size());

    int cnt = 0;
    int one = 0;
    int zero = 0;

    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '0') zero++;
    }

    cnt = zero;

    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            zero--;
        } else {
            one++;
        }

        cnt = min(cnt, zero + one);
    }

    one = 0;
    zero = 0;
    reverse(s.begin(), s.end());
    
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '0') zero++;
    }

    cnt = min(cnt, zero);

    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            zero--;
        } else {
            one++;
        }

        cnt = min(cnt, zero + one);
    }
    cout << cnt << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
