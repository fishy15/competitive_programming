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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    multiset<int> cur;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        auto it = cur.upper_bound(x);
        if (it != cur.end()) {
            cur.erase(it);
        }
        cur.insert(x);
    }

    cout << (int)(cur.size()) << '\n';

    return 0;
}
