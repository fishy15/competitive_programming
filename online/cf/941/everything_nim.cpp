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

    set<int> piles;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        piles.insert(x);
    }
    
    int p = 0;
    vector<int> diffs;
    for (auto x : piles) {
        diffs.push_back(x - p);
        p = x;
    }

    int sz = diffs.size();
    bool first_wins = true;
    for (int i = sz - 2; i >= 0; i--) {
        if (diffs[i] == 1) {
            // whoever goes first must go second next turn
            first_wins = !first_wins;
        } else {
            first_wins = true;
        }
    }

    if (first_wins) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
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
