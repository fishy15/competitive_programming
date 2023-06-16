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
#define MAXN 100010

using namespace std;

int n;
pair<ll, int> nums[MAXN];
set<pair<ll, int>> ans;

void add(ll n, int p) {
    ans.insert({n, p});
    p = 32 - p;

    if ((n & (1LL << p)) != 0) {
        n -= 1LL << p;
    }

    if (ans.count({n, 32 - p}) && ans.count({n + (1LL << p), 32 - p})) {
        ans.erase({n, 32 - p});
        ans.erase({n + (1LL << p), 32 - p});
        add(n, 32 - p - 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    string trash; getline(cin, trash);
    for (int i = 0; i < n; i++) {
        int a;
        ll x = 0;
        char c;
        cin >> a;
        x += a * (1LL << 24);
        cin >> c;
        cin >> a;
        x += a * (1LL << 16);
        cin >> c;
        cin >> a;
        x += a * (1LL << 8);
        cin >> c;
        cin >> a;
        x += a;
        cin >> c;
        int p; cin >> p;
        nums[i] = {x, p};
    }

    sort(nums, nums + n, [](auto a, auto b) {
        return a.second == b.second ? a.first < b.first : a.second < b.second;
    });

    for (int i = 0; i < n; i++) {
        auto [n, p] = nums[i];

        ll n2 = n;
        bool skip = false;
        while (p >= 0) {
            if (ans.count({n2, p})) {
                skip = true;
                break;
            }

            p = 32 - p;
            if (n2 & (1LL << p)) {
                n2 -= 1LL << p;
            } 
            p = 32 - p;

            p--;
        }

        if (!skip) {
            add(nums[i].first, nums[i].second);
        }
    }

    for (auto [n, p] : ans) {
        cout << ((n >> 24) & 0xff) << '.' << ((n >> 16) & 0xff) << '.' << ((n >> 8) & 0xff) << '.' << (n & 0xff) << '/' << p << '\n';
    }

    return 0;
}
