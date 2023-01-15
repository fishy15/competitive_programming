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
#include <optional>
#include <cassert>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

template<typename T>
deque<ll> solve(T start, T end, ll bound) {
    if (start == end) {
        return {};
    } else if (end - start == 1) {
        return {0};
    } else {
        int n = end - start;
        if (end[-1] == 1) {
            for (int i = 0; i < n; i++) {
                start[i] *= -1;
            }
        }

        vector<ll> psum(n - 1);
        psum[n - 2] = start[n - 2];
        for (int i = n - 3; i >= 0; i--) {
            psum[i] = start[i] + psum[i + 1];
        }

        deque<ll> ans(n);
        iota(ans.begin(), ans.end() - 1, -1'000'000);

        ll cur_val = 0;
        for (int i = 0; i < n - 1; i++) {
            cur_val += ans[i] * start[i];
        }

        if (cur_val >= n - 1) {
            ans[n - 1] = cur_val;
            return ans;
        } else {
            for (int i = 0; i < n - 1; i++) {
                ll m = psum[i] - 1;

                ll needed;
                if (m > 0) {
                    needed = ((n - 1) - cur_val + m - 1) / m;
                } else if (m < 0 && i == 0) {
                    m *= -1;
                    needed = ((n - 1) - cur_val + m - 1) / m;
                    needed *= -1;
                    m *= -1;
                } else {
                    continue;
                }

                if (cur_val + psum[i] * needed > bound) {
                    continue;
                }

                for (int j = i; j < n - 1; j++) {
                    ans[j] += needed;
                }

                for (int j = 0; j < n - 1; j++) {
                    ans[n - 1] += ans[j] * start[j];
                }

                return ans;
            }

            return {};
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    auto res = solve(a.begin(), a.end(), 1'000'000'000'000LL);
    if (!res.empty()) {
        cout << "Yes\n";
        for (ll x : res) {
            cout << x << ' ';
        }
        cout << '\n';
    } else {
        cout << "No\n";
    }

    return 0;
}
