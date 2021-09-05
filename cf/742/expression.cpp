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

void solve() {
    int s, n; cin >> s >> n;
    string ss = to_string(s);

    vector<int> ans;
    int cur_mul = 1;
    int sz = ss.size();
    for (int i = sz - 1; i >= 0; i--) {
        for (int j = 0; j < ss[i] - '0'; j++) {
            ans.push_back(cur_mul);
        }
        cur_mul *= 10;
    }

    while ((int) ans.size() > n) {
        int back = ans.back();
        ans.pop_back();
        ans.back() += back;
    }

    int pos = 0;
    while ((int) ans.size() < n) {
        if (ans[pos] == 1) {
            pos++;
        } else {
            int cur_p = 1;
            while (10 * cur_p < ans[pos]) cur_p *= 10;
            ans[pos] -= cur_p;
            ans.push_back(cur_p);
        }
    }

    for (int i : ans) {
        cout << i << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
