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

int n;
string s;
string ans;
set<char> cur;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;
    n = (int)(s.size());

    for (int i = 0; i < n; i++) {
        cur.insert(s[i]);
        if (cur.size() == 4) {
            ans += s[i];
            cur = {};
        }
    }

    for (char c : {'A', 'C', 'T', 'G'}) {
        if (!cur.count(c)) {
            ans += c;
            break;
        }
    }

    cout << ans << '\n';

    return 0;
}
