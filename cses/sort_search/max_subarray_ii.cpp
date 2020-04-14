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

int n, a, b;
int nums[MAXN];
ll pre[MAXN + 1];
multiset<ll> cur;
ll ans = -INFLL;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + nums[i - 1];
    }

    for (int i = 0; i <= n; i++) {
        if (i - a >= 0) {
            cur.insert(pre[i - a]);
        }

        if (i - b - 1 >= 0) {
            cur.erase(cur.find(pre[i - b - 1]));
        }

        if (i - a >= 0) ans = max(ans, pre[i] - *cur.begin());
    }

    cout << ans << '\n';

    return 0;
}
