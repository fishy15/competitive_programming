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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> t(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }

    ll total = accumulate(a.begin(), a.end(), 0LL);
    if (n == 2 && a[0] == a[1]) {
        cout << "0.25\n";
        for (auto x : p) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    } else if (2 * a[p[0]] >= total) {
        cout << "0.5\n";
        for (auto x : p) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    } else {
        cout << "1\n";
        for (int i = 1; i < n; i++) {
            cout << p[i] + 1 << ' ';
        }
        cout << p[0] + 1 << '\n';
    }


    return 0;
}
