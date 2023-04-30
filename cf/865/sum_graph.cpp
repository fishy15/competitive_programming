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

void add(int x) {
    cout << "+ " << x << endl;
    
    int res;
    cin >> res;
    if (res == -2) {
        exit(0);
    }
}

int ask(int i, int j) {
    cout << "? " << i << ' ' << j << endl;

    int res;
    cin >> res;
    if (res == -2) {
        exit(0);
    }

    return res;
}

void ans(const vector<int> &p1, const vector<int> &p2) {
    cout << "! ";
    for (auto x : p1) {
        cout << x << ' ';
    }

    int n = p2.size();
    for (int i = 0; i < n; i++) {
        cout << p2[i];
        if (i == n - 1) {
            cout << endl;
        } else {
            cout << ' ';
        }
    }

    int res;
    cin >> res;
    if (res == -2) {
        exit(0);
    }
}

void solve() {
    int n;
    cin >> n;

    if (n == 2) {
        ans({1, 2}, {2, 1});
    } else {
        add(n);
        add(n + 1);

        // find one end
        pair<int, int> best = {0, 1};
        for (int i = 2; i <= n; i++) {
            auto d = ask(1, i);
            best = max(best, {d, i});
        }

        vector<int> at_dist(n);
        for (int i = 1; i <= n; i++) {
            if (i == best.second) {
                at_dist[0] = best.second;
            } else {
                auto d = ask(best.second, i);
                at_dist[d] = i;
            }
        }

        vector<int> base_perm;
        for (int i = 0; i < n / 2; i++) {
            base_perm.push_back(n - i - 1);
            base_perm.push_back(i);
        }

        if (n % 2 == 1) {
            base_perm.push_back(n / 2);
        }

        reverse(base_perm.begin(), base_perm.end());

        vector<int> ans1(n), ans2(n);
        for (int i = 0; i < n; i++) {
            ans1[at_dist[i] - 1] = base_perm[i] + 1;
            ans2[at_dist[i] - 1] = base_perm[n - i - 1] + 1;
        }

        ans(ans1, ans2);
    }
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
