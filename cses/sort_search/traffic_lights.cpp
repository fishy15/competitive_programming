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

int n, x;
set<int> cur;
multiset<int> dist;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> x >> n;
    cur = {0, x};
    dist = {x};
    for (int i = 0; i < n; i++) {
        int v; cin >> v;
        auto it = cur.lower_bound(v);
        int v1 = *it;
        it--;
        int v2 = *it;
        /* cout << v1 << ' ' << v2 << '\n'; */
        cur.insert(v);
        dist.erase(dist.find(v1 - v2));
        dist.insert(v - v2);
        dist.insert(v1 - v);
        cout << *dist.rbegin() << ' ';
    }
    cout << '\n';

    return 0;
}
