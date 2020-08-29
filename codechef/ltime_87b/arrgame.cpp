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
    vector<int> a;
    vector<int> b;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a.push_back(x);
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i]) {
            if (cnt) b.push_back(cnt);
            cnt = 0;
        } else if (!a[i]) {
            cnt++;
        }
    }

    sort(b.begin(), b.end(), greater<int>());
    if (b.empty()) {
        cout << "No\n";
    } else if (b.size() == 1 || b[0] > b[1] * 2) {
        if (b[0] % 2 == 1) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    } else {
        cout << "No\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
