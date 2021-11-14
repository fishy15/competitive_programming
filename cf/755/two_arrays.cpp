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
    vector<int> a(n);
    multiset<int> b;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        b.insert(x);
    }

    sort(a.rbegin(), a.rend());

    for (int x : a) {
        multiset<int>::iterator it;
        if ((it = b.find(x + 1)) != b.end()) {
            b.erase(it);
        } else if ((it = b.find(x)) != b.end()) {
            b.erase(it);
        } else {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
