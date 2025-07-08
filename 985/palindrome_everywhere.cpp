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

void solve() {
    int n;
    string s;
    cin >> n >> s;

    auto b_cnt = count(all(s), 'B');
    auto r_cnt = count(all(s), 'R');
    if (b_cnt <= 1 || r_cnt <= 1) {
        cout << "YES\n";
        return;
    }

    auto diff_char = (s[0] == 'B') ? 'R' : 'B';
    auto rotate_it = find(all(s), diff_char);
    rotate(begin(s), rotate_it, end(s));

    vector<int> groups;
    bool b_big = false;
    bool r_big = false;
    int cur = 0;
    rep(i, 0, n) {
        if (i > 0 && s[i - 1] != s[i]) {
            if (cur > 1) {
                if (s[i-1] == 'B') b_big = true;
                else r_big = true;
                groups.push_back(cur);
            }
            cur = 0;
        }
        cur++;
    }

    // final group
    if (cur > 1) {
        if (s[n-1] == 'B') b_big = true;
        else r_big = true;
        groups.push_back(cur);
    }

    if (b_big && r_big) {
        cout << "NO\n";
    } else {
        if (count_if(all(groups), [](int x) { return x % 2 == 0; }) == 1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
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
