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

bool try_out(int n, const string &s, bool first, bool second) {
    vector<bool> ans = {first, second};
    rep(i, 1, n-1) {
        ans.push_back(end(ans)[-1] ^ end(ans)[-2] ^ (s[i] == 'o'));
    }

    // check everything
    rep(i, 0, n) {
        auto a = ans[(i + n - 1) % n];
        auto b = ans[i];
        auto c = ans[(i + 1) % n];
        if ((a ^ b ^ c) != (s[i] == 'o')) {
            return false;
        }
    }

    for (auto x : ans) {
        cout << (x ? "S" : "W");
    }
    cout << '\n';

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    string s;
    cin >> s;

    if (try_out(n, s, true, true)) return 0;
    if (try_out(n, s, true, false)) return 0;
    if (try_out(n, s, false, true)) return 0;
    if (try_out(n, s, false, false)) return 0;

    cout << "-1\n";

    return 0;
}
