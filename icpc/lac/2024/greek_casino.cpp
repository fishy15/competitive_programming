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
#define ld double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010

using namespace std;

ll w[MAXN];
ld E[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    auto tot = accumulate(w + 1, w + n + 1, 0LL);

    // probability you get a divisor of i
    vector<ll> sum_divisors(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            sum_divisors[j] += w[i];
        }
    }

    for (int i = n; i >= 1; i--) {
        vector<ll> w_sum = {0};
        for (int mul = 1; i * mul <= n; mul++) {
            int lcm = i * mul;
            w_sum.push_back(sum_divisors[lcm]);
        }

        for (int j = 1; j < (int) w_sum.size(); j++) {
            for (int k = 2 * j; k < (int) w_sum.size(); k += j) {
                w_sum[k] -= w_sum[j];
            }
        }

        ld exp_up = 0;
        for (int mul = 2; mul < (int) w_sum.size(); mul++) {
            exp_up += (ld) w_sum[mul] / tot * E[i * mul];
        }

        auto p_same = (ld) w_sum[1] / tot;
        E[i] = (exp_up + 1) / (1 - p_same);
    }

    cout << fixed << setprecision(15);
    cout << E[1] - 1 << '\n';

    return 0;
}
