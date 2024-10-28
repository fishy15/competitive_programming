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

bool ask(const string &s) {
    cout << "? " << s << endl;
    int x;
    cin >> x;
    return x == 1;
}

void answer(const string &s) {
    cout << "! " << s << endl;
}

void solve() {
    int n;
    cin >> n;

    // get first character
    bool has_zero = ask("0");
    if (!has_zero) {
        auto ans = string(n, '1');
        answer(ans);
        return;
    }

    string cur = "0";
    bool add_front = false;

    while (sz(cur) < n) {
        if (add_front) {
            if (ask("0"s + cur)) {
                cur = "0"s + cur;
            } else {
                cur = "1"s + cur;
            }
        } else {
            if (ask(cur + "0")) {
                cur += '0';
            } else if (ask(cur + "1")) {
                cur += '1';
            } else {
                add_front = true;
            }
        }
    }

    answer(cur);
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
