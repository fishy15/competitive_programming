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
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, t;
    cin >> n >> t;

    vector<array<int, 3>> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i][0] >> nums[i][1] >> nums[i][2];
    }

    ld l = 0;
    ld r = t;
    
    auto comp = [&nums](ld m) {
        ld total = 0;
        for (auto [a, b, d] : nums) {
            ld val = (ld) d * m;
            val = clamp<ld>(val, a, b);
            total += val;
        }
        return total;
    };

    for (int i = 0; i < 200; i++) {
        ld m = l + (r - l) / 2;
        auto prop = comp(m);
        if (prop < t) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << fixed << setprecision(15);
    for (auto [a, b, d] : nums) {
        ld val = (ld) d * l;
        val = clamp<ld>(val, a, b);
        cout << val << '\n';
    }

    return 0;
}
