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

int dec(int d) {
    if (d == 0) {
        return 9;
    } else {
        return d - 1;
    }
}

void solve() {
    int n; cin >> n;
    string s = to_string(n);

    int tot = s.size();
    int sz = max(0, tot - 2);
    ll tot_ans = 0;
    for (int m = 0; m < (1 << sz); m++) {
        int mm = m << 2;
        ll ans = 1;
        for (int i = 0; i < tot; i++) {
            // if needs to carry
            if ((m >> i) & 1) {
                int dig = s[tot - i - 1] - '0'; 
                if ((mm >> i) & 1) dig = dec(dig);
                if (dig != 9) dig += 10;
                ans *= 19 - dig;
            } else {
                int dig = s[tot - i - 1] - '0'; 
                if ((mm >> i) & 1) {
                    // impossible to do 
                    if (dig == 0) {
                        ans *= 0; 
                        break;
                    }
                    dig = dec(dig);
                }
                ans *= (dig + 1);
            }
        }
        tot_ans += ans;
    }

    cout << tot_ans - 2 << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
