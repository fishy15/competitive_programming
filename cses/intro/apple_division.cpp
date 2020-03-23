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
int nums[20];
ll sum;
ll ans = INFLL;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        sum += nums[i];
    }

    for (int i = 0; i <= (1 << n); i++) {
        ll s = 0;
        for (int j = 0; j < n; j++) {
            if ((1 << j) & i) {
                s += nums[j];
            }
        }
        ans = min(ans, abs(sum - 2 * s));
    }

    cout << ans << '\n';

    return 0;
}
