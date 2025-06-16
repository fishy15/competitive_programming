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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

bool works(int use, const array<int, 26> &cnts) {
    auto n = accumulate(all(cnts), 0) - 1;
    rep(i, 0, 26) {
        if (i == use) {
            if (cnts[i]-1 > n / 2) {
                return false;
            }
        } else {
            if (cnts[i] > (n + 1) / 2) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    cin >> s;

    int n = sz(s);
    array<int, 26> cnts{};
    rep(i, 0, n) {
        cnts[s[i] - 'A']++;
    }

    int last = -1;
    string ans;
    rep(i, 0, n) {
        int res = -1;
        rep(c, 0, 26) {
            if (cnts[c] > 0 && c != last && works(c, cnts)) {
                res = c;
                break;
            }
        }

        if (res == -1) {
            cout << "-1\n";
            return 0;
        }

        ans += (char) (res + 'A');
        last = res;
        cnts[res]--;
    }

    cout << ans << '\n';

    return 0;
}
