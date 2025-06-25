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

// change if necessary
#define MAXN 1000000

using namespace std;

bool solve(const vector<int> &a, const vector<int> &b, const vector<int> &c, int ord) {
    int n = (int) a.size();
    auto tot = accumulate(a.begin(), a.end(), 0LL);
    auto needed = (tot + 2) / 3;

    int i = 0;
    ll a_sum = 0;
    ll b_sum = 0;
    ll c_sum = 0;

    int start1, start2, start3;
    int end1, end2, end3;

    start1 = 0;
    while (i < n && a_sum < needed) {
        a_sum += a[i++];
    }
    end1 = i;

    start2 = i;
    while (i < n && b_sum < needed) {
        b_sum += b[i++];
    }
    end2 = i;

    start3 = i;
    while (i < n && c_sum < needed) {
        c_sum += c[i++];
    }
    end3 = n;

    auto pr1 = [&] { cout << start1+1 << ' ' << end1 << ' '; };
    auto pr2 = [&] { cout << start2+1 << ' ' << end2 << ' '; };
    auto pr3 = [&] { cout << start3+1 << ' ' << end3 << ' '; };

    if (min({a_sum, b_sum, c_sum}) >= needed) {
        if (ord == 0) { pr1(); pr2(); pr3(); }
        if (ord == 1) { pr1(); pr3(); pr2(); }
        if (ord == 2) { pr2(); pr1(); pr3(); }
        if (ord == 3) { pr3(); pr1(); pr2(); }
        if (ord == 4) { pr2(); pr3(); pr1(); }
        if (ord == 5) { pr3(); pr2(); pr1(); }
        cout << '\n';
        return true;
    } else {
        return false;
    }
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n), b(n), c(n);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;
    for (auto &x : c) cin >> x;

    if (solve(a, b, c, 0)) return;
    if (solve(a, c, b, 1)) return;
    if (solve(b, a, c, 2)) return;
    if (solve(b, c, a, 3)) return;
    if (solve(c, a, b, 4)) return;
    if (solve(c, b, a, 5)) return;

    cout << "-1\n";
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
