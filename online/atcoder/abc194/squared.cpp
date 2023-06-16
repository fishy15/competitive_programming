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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 300010

using namespace std;

int n;
ll nums[MAXN];
ll ans;
ll sum;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        ans += n * (nums[i] * nums[i]) * 2;
        sum += nums[i];
    }

    for (int i = 0; i < n; i++) {
        ans -= 2 * nums[i] * sum;
    }

    ans /= 2;
    cout << ans << '\n';

    return 0;
}
