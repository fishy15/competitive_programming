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
ll x;
ll nums[MAXN];
ll pre[MAXN + 1];
ll ans;
map<ll, int> p;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        pre[i + 1] = pre[i] + nums[i];
    }

    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        ans += p[pre[i] - x];
        p[pre[i]]++;
    }

    cout << ans << '\n';

    return 0;
}
