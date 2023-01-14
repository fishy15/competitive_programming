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

ll n;
string s;
int sz;
ll ans = 0;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    s = to_string(n);
    sz = s.size();

    for (int i = 0; i < sz; i++) {
        for (int j = 1; i + j <= sz; j++) {
            string cur;
            for (int k = 0; k < i; k++) cur += '0';
            for (int k = 0; k < j; k++) cur += '1';

            string pre = s.substr(0, i + j);
            if (cur == pre) {
                string res = s.substr(i + j, sz - i - j);
                if (res.empty()) ans++;
                else ans += (ll) (stoll(res) + 1);
            } else if (stoll(cur) < stoll(pre)) {
                ll cur = 1;
                for (int k = 0; k < sz - i - j; k++) cur *= 10;
                ans += cur;
            }
        }
    }

    cout << ans << '\n';

    
    return 0;
}
