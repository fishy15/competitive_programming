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
#define MAXN 100000

using namespace std;

int n;
ll a, b; 
ll nums[MAXN];
ll ans = INFLL;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> a >> b;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    sort(nums, nums + n);

    int cur = 0;
    int upcur = 0;
    ll updist = 0;
    int downcur = 0;
    ll downdist = 0;

    upcur = n;

    for (int i = 0; i < n; i++) {
        updist += nums[i];
    }

    for (int i = 0; i < n; i++) {
        downcur++;
        upcur--;
        downdist += downcur * (nums[i] - cur);
        updist -= upcur * (nums[i] - cur);
        ans = min(ans, downcur * b + upcur * a);
        cur = nums[i];
        cout << i << ' ' << updist << ' ' << downdist << '\n';
    }

    cout << ans << '\n';

    return 0;
}
