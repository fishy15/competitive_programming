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

void solve() {
    int n; cin >> n;
    set<int> a;

    for (int i = 0; i < 30; i++) {
        a.insert(1 << i);
    }

    int cur = 1;
    ll sum = 0;
    while ((int) a.size() < n) {
        while (a.count(cur)) cur++;
        a.insert(cur);
        cur++;
    }

    // submit first n numbers
    for (int x : a) {
        cout << x << ' ';
        sum += x;
    }
    cout << endl;

    vector<ll> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        sum += b[i];
    }

    vector<int> ans;
    ll left = sum / 2;
    for (int x : b) {
        if (x < left) {
            ans.push_back(x);
            left -= x;
        }
    }

    for (int i = 0; i < 30; i++) {
        if (left & (1 << i)) {
            ans.push_back(1 << i);
        }
    }

    for (int x : ans) {
        cout << x << ' ';
    }
    cout << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
