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
    int n, m;
    cin >> n >> m;

    vector<int> ans(n, -1);
    set<int> added;
    
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        added.insert(x);

        auto idx = (int) added.size() - 1;
        if (ans[idx] == -1) {
            ans[idx] = i + 1;
        }
    }

    reverse(ans.begin(), ans.end());
    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
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
