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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1010
#define MAX 1000010

using namespace std;

int n;
ll nums[MAXN];
bool is_power[MAX];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    ll g = 0;
    for (int i = 0; i < n; i++) {
        g = gcd(g, nums[i]);
    }


    for (ll i = 2; i < MAX; i++) {
        if (!is_power[i]) {
            ll i2 = i * i;
            while (i2 < MAX) {
                is_power[i2] = true;
                i2 *= i;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= g; i++) {
        if (is_power[i] && g % i == 0) {
            ans = max(ans, i);
        }
    }

    if (ans == 0) {
        cout << "NO CIVIL WAR\n";
    } else {
        cout << ans << '\n';
    }


    return 0;
}
