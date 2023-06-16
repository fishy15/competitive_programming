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
#define MAXN 200000

using namespace std;

int n;
vector<pair<ll, int>> a;
vector<ll> b;
multiset<ll> cur;
int ans[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i <= n; i++) {
        ll x; cin >> x;
        a.push_back({x, i});
    }

    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        b.push_back(x);
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (int i = 0; i < n; i++) {
        cur.insert(a[i].first - b[i]);
    }

    ans[a[n].second] = *cur.rbegin();

    for (int i = n - 1; i >= 0; i--) {
        cur.erase(cur.find(a[i].first - b[i]));
        cur.insert(a[i + 1].first - b[i]);
        ans[a[i].second] = *cur.rbegin();
    }

    for (int i = 0; i <= n; i++) {
        cout << ans[i] << ' ';
    } cout << '\n';

    return 0;
}
