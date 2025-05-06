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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

struct halves {
    multiset<int> lower, higher;
    ll low_sum = 0;
    ll high_sum = 0;

    void insert(int x) {
        if (higher.empty()) {
            higher.insert(x);
            high_sum += x;
        } else if (x < *begin(higher)) {
            lower.insert(x);
            low_sum += x;
        } else {
            higher.insert(x);
            high_sum += x;
        }
        rebalance();
    }

    void rebalance() {
        int tot = sz(lower) + sz(higher);
        while (sz(lower) > tot / 2) {
            auto x = *prev(end(lower));
            lower.erase(lower.find(x));
            higher.insert(x);
            low_sum -= x;
            high_sum += x;
        }
        while (sz(higher) > (tot + 1) / 2) {
            auto x = *begin(higher);
            higher.erase(higher.find(x));
            lower.insert(x);
            high_sum -= x;
            low_sum += x;
        }
    }

    void pr() {
        cout << "lo: ";
        for (auto x : lower) cout << x << ' ';
        cout << '\n';
        cout << low_sum << '\n';
        cout << "hi: ";
        for (auto x : higher) cout << x << ' ';
        cout << '\n';
        cout << high_sum << '\n';
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    vector<ll> pref(n+1), suff(n+1);
    halves from_front;
    rep(i, 0, n) {
        if (i % 2 == 0) {
            pref[i] = from_front.high_sum - from_front.low_sum;
        }
        from_front.insert(nums[i]);
    }

    halves from_back;
    for (int i = n-1; i >= 0; i--) {
        if ((i + 1) % 2 == n % 2) {
            suff[i+1] = from_back.high_sum - from_back.low_sum;
        }
        from_back.insert(nums[i]);
    }

    if (n % 2 == 0) {
        cout << from_front.high_sum - from_front.low_sum << '\n';
    } else {
        ll best = 0;
        for (int i = 0; i <= n; i += 2) {
            best = max(best, pref[i] + suff[i+1]);
        }
        cout << best << '\n';
    }

    return 0;
}
