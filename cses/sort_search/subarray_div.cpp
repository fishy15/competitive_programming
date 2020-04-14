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

int n;
ll nums[MAXN];
ll d[MAXN];
ll ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    ll cur = 0;
    d[0]++;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        cur += nums[i] % n;
        if (cur < n) cur += n;
        if (cur >= n) cur -= n;
        d[cur]++;
    }

    for (int i = 0; i < n; i++) {
        ans += d[i] * (d[i] - 1) / 2;
    }

    cout << ans << '\n';

    return 0;
}
