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
#define MAXN 100000

using namespace std;

ll fib[MAXN + 10];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s; cin >> s;
    int n = (int)(s.size());

    fib[0] = 1;
    fib[1] = 1;

    for (int i = 2; i < MAXN + 3; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        if (fib[i] >= MOD) fib[i] -= MOD;
    }

    char prev = '`';
    int cur = 0;
    ll ans = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'm' || s[i] == 'w') {
            cout << "0\n";
            return 0;
        }
        
        if (s[i] != prev) {
            if (prev == 'u' || prev == 'n') {
                ans *= fib[cur];
                ans %= MOD;
            } 

            cur = 1;
        } else {
            cur++;
        }
        prev = s[i];
    }

    if (prev == 'u' || prev == 'n') {
        ans *= fib[cur];
        ans %= MOD;
    } 

    cout << ans << '\n';

    return 0;
}
