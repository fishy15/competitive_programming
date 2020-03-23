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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n; cin >> n;
    vector<vector<int>> ok;

    for (int i = 0; i < n; i++) {
        int k; cin >> k;
        vector<int> cur;
        for (int j = 0; j < k; j++) {
            int x; cin >> x;
            cur.push_back(x);
        }
        ok.push_back(cur);
    }

    set<int> used;
    int pos = -1;
    for (int i = 0; i < n; i++) {
        bool done = false;
        for (int j : ok[i]) {
            if (!used.count(j)) {
                used.insert(j);
                done = true;
                break;
            }
        }

        if (!done) {
            pos = i + 1;
        }
    }

    int miss = -1;
    for (int i = 1; i <= n; i++) {
        if (!used.count(i)) {
            miss = i;
            break;
        }
    }

    if (miss == -1) {
        cout << "OPTIMAL\n";
    } else {
        cout << "IMPROVE\n";
        cout << pos << ' ' << miss << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
