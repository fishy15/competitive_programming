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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 5010

using namespace std;

int n;
int nums[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    ll res = INFLL;
    for (int i = 0; i < n; i++) {
        ll cur = 0;
        ll ans = 0;
        for (int j = i - 1; j >= 0; j--) {
            cur++;
            ll a = (cur + nums[j] - 1) / nums[j];
            ans += a;
            cur = nums[j] * a;
        }

        cur = 0;
        for (int j = i + 1; j < n; j++) {
            cur++;
            ll a = (cur + nums[j] - 1) / nums[j];
            ans += a;
            cur = nums[j] * a;
        }

        res = min(res, ans);
    }
    
    cout << res << '\n';

    return 0;
}
