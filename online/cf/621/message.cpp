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

int n;
string s; 

ll check1(char a) {
    ll c = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == a) {
            c++;
        }
    }

    return c;
}

ll check2(char a, char b) {
    int c2 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == b) {
            c2++;
        }
    }

    int qq = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == b) {
            c2--;
        } else if (s[i] == a) {
            qq += c2;
        }
    }

    return qq;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;
    n = (int)(s.length());
    ll ans = 0;

    for (char a = 'a'; a <= 'z'; a++) {
        ll q = check1(a);
        ans = max(ans, check1(a));
        ans = max(ans, q * (q - 1) / 2);
    }

    for (char a = 'a'; a <= 'z'; a++) {
        for (char b = 'a'; b <= 'z'; b++) {
            ans = max(ans, check2(a, b));
        }
    }

    cout << ans << '\n';

    return 0;
}
