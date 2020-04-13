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

int n, m;
multiset<int> nums;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.insert(x);
    }

    for (int i = 0; i < m; i++) {
        int v; cin >> v;
        auto it = nums.upper_bound(v);
        if (it != nums.begin()) {
            it--;
            cout << *it << '\n';
            nums.erase(it);
        } else {
            cout << -1 << '\n';
        }
    }

    return 0;
}
