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
    int n; cin >> n;
    string s; cin >> s;
    set<int> one;
    set<int> zero;
    int tot = 0;
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        int x = s[i] - '0';
        if (x == 0) {
            if (!one.empty()) {
                ans[i] = *one.begin();
                zero.insert(*one.begin());
                one.erase(one.begin());
            } else {
                ans[i] = ++tot;
                zero.insert(ans[i]);
            }
        } else {
            if (!zero.empty()) {
                ans[i] = *zero.begin();
                zero.erase(*zero.begin());
                one.insert(ans[i]);
            } else {
                ans[i] = ++tot;
                one.insert(ans[i]);
            }
        }
    }
    cout << tot << '\n';
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
