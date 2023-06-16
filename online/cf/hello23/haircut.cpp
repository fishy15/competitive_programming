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
    int n;
    cin >> n;

    vector<int> a(n), b(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    int m;
    cin >> m;

    multiset<int> x;

    for (int i = 0; i < m; i++) {
        int xi;
        cin >> xi;
        x.insert(xi);
    }

    vector<int> razors;
    for (int i = 0; i < n; i++) {
        if (a[i] < b[i]) {
            cout << "NO\n";
            return;
        } else {
            while (!razors.empty() && razors.back() < b[i]) {
                razors.pop_back();
            }

            if (a[i] != b[i] && (razors.empty() || razors.back() != b[i])) {
                auto it = x.find(b[i]);
                if (it == x.end()) {
                    cout << "NO\n";
                    return;
                } else {
                    razors.push_back(*it);
                    x.erase(it);
                }
            }
        }
    }

    cout << "YES\n";
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
