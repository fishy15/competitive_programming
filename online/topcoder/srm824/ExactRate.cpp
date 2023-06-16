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

struct ExactRate {
    vector<bool> get(int n, ll seed, int t) {
        vector<bool> h(n);

        for (int i = 0; i < n; i++) {
            seed = (seed * 1103515245 + 12345) % (1 << 31);
            h[i] = (seed > t);
        }

        return h;
    }

    ll gcd(ll a, ll b) {
        return b ? gcd(b, a % b) : a;
    }

    int check(int len, const vector<bool> &nums, int s, int f) {
        array<ll, 2> cnt = {0, 0};

        for (int i = 0; i < len; i++) {
            cnt[nums[i]]++;
        }

        if (nums[0] * s == nums[1] * f) {
            return 0;
        }

        int n = nums.size();
        for (int i = 1; i + len <= n; i++) {
            cnt[nums[i - 1]]--;
            cnt[nums[i + len - 1]]++;

            if (nums[0] * s == nums[1] * f) {
                return i;
            }
        }

        return -1;
    }

    vector<int> getLongest(int n, int seed, int t, int s, int f) {
        auto nums = get(n, seed, t);

        int g = gcd(s, f);
        s /= g;
        f /= g;

        int l = 1;
        int r = n / (s + f);
        pair<int, int> ans = {-1, -1};

        while (l <= r) {
            int m = (l + r) / 2 * (s + f);
            int idx = check(m, nums, s, f);

            if (idx != -1) {
                ans = {m, idx};
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        if (ans.first == -1) {
            return {0, 0};
        } else {
            return {ans.second, ans.first + ans.second};
        }
    }
};
