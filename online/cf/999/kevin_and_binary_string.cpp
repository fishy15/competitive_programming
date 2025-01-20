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

tuple<deque<int>, deque<int>, bool> compress(const string &s) {
    char cur = 's';
    int cnt = 0;
    deque<int> zero, one;

    auto proc = [&] {
        if (cur == '0') {
            zero.push_back(cnt);
        } else if (cur == '1') {
            one.push_back(cnt);
        }
    };

    for (auto c : s) {
        if (c != cur) {
            proc();
            cur = c;
            cnt = 1;
        } else {
            cnt++;
        }
    }

    proc();

    return tuple{zero, one, s[0] == '0'};
}

void solve() {
    string s, t;
    cin >> s >> t;

    auto [s0, s1, s_zero] = compress(s);
    auto [t0, t1, t_zero] = compress(t);

    int ops = 0;
    auto skip = [&] {
        if (s_zero) {
            if (sz(s0) <= 1) return false;
            s0[1] += s0[0];
            s0.pop_front();
        } else {
            if (sz(s1) <= 1) return false;
            s1[1] += s1[0];
            s1.pop_front();
        }
        s_zero = !s_zero;
        return true;
    };

    if (s_zero != t_zero) {
        skip();
        ops++;
    }

    while (!t0.empty() || !t1.empty()) {
        if (t_zero) {
            if (t0.empty()) break;
            while (!s0.empty() && s0.front() != t0.front()) {
                ops++;
                bool ok = skip();
                if (ok) ok = skip();
                if (!ok) break;
            }
            if (s0.empty() || s0.front() != t0.front()) {
                cout << "-1\n";
                return;
            }
            s0.pop_front();
            t0.pop_front();
        } else {
            if (t1.empty()) break;
            while (!s1.empty() && s1.front() != t1.front()) {
                ops++;
                bool ok = skip();
                if (ok) ok = skip();
                if (!ok) break;
            }
            if (s1.empty() || s1.front() != t1.front()) {
                cout << "-1\n";
                return;
            }
            s1.pop_front();
            t1.pop_front();
        }
        s_zero = !s_zero;
        t_zero = !t_zero;
    }

    cout << ops << '\n';
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
