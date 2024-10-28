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
    int n, m, k;
    cin >> n >> m >> k;

    multiset<int> a, b;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.insert(x);
    }
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        b.insert(x);
    }

    vector<ll> ans;
    ans.push_back(accumulate(a.begin(), a.end(), 0LL));
    int first = true;
    while (true) {
        auto &my = first ? a : b;
        auto &other = first ? b : a;

        int my_low = *my.begin();
        int other_high = *other.rbegin();

        if (my_low < other_high) {
            my.erase(my.begin());
            other.erase(prev(other.end()));
            my.insert(other_high);
            other.insert(my_low);
        }
        
        ans.push_back(accumulate(a.begin(), a.end(), 0LL));
        first = !first;

        auto end = ans.end();
        if (ans.size() >= 4 && end[-4] == end[-2] && end[-3] == end[-1]) {
            break;
        }
    }

    if (k < (int) ans.size()) {
        cout << ans[k] << '\n';
    } else {
        if ((int) ans.size() % 2 == k % 2) {
            cout << ans.end()[-2] << '\n';
        } else {
            cout << ans.end()[-1] << '\n';
        }
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
