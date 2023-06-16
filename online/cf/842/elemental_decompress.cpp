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

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> p(n), q(n);
    set<int> left_p, left_q;
    for (int i = 1; i <= n; i++) {
        left_p.insert(i);
        left_q.insert(i);
    }

    for (int i = 0; i < n; i++) {
        if (left_p.count(a[i])) {
            p[i] = a[i];
            left_p.erase(a[i]);
        } else if (left_q.count(a[i])) {
            q[i] = a[i];
            left_q.erase(a[i]);
        } else {
            cout << "NO\n";
            return;
        }
    }

    vector<int> empty_p, empty_q;
    for (int i = 0; i < n; i++) {
        if (p[i] == 0) {
            empty_p.push_back(i);
        } else {
            empty_q.push_back(i);
        }
    }

    sort(empty_p.begin(), empty_p.end(), [&](int i, int j) {
        return q[i] < q[j];
    });

    sort(empty_q.begin(), empty_q.end(), [&](int i, int j) {
        return p[i] < p[j];
    });

    auto p_it = left_p.begin();
    auto q_it = left_q.begin();

    for (auto pi : empty_p) {
        p[pi] = *p_it;
        p_it++;
    }

    for (auto qi : empty_q) {
        q[qi] = *q_it;
        q_it++;
    }

    for (int i = 0; i < n; i++) {
        if (max(p[i], q[i]) != a[i]) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";

    for (int x : p) {
        cout << x << ' ';
    }
    cout << '\n';

    for (int x : q) {
        cout << x << ' ';
    }
    cout << '\n';
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
