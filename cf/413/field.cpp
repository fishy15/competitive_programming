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

int a, b;
int h, w;
int n;
vector<int> nums;
map<pair<ll, ll>, int> dp;

bool comp(pair<ll, ll> p) {
    return ((p.first >= a && p.second >= b) || (p.first >= b && p.second >= a));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> a >> b >> h >> w >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    sort(nums.rbegin(), nums.rend());

    dp[make_pair(h, w)] = 0;

    if (comp({h, w})) {
        cout << "0\n";
        return 0;
    }

    for (int x : nums) {
        if (x == 1) break;
        vector<pair<pair<ll, ll>, int>> cur;
        for (auto p : dp) {
            pair<ll, ll> p1 = {p.first.first * x, p.first.second};
            pair<ll, ll> p2 = {p.first.first, p.first.second * x};

            if (dp.find(p1) == dp.end() || dp[p1] > p.second + 1) {
                cur.push_back({p1, p.second + 1});
            }

            if (dp.find(p2) == dp.end() || dp[p2] > p.second + 1) {
                cur.push_back({p2, p.second + 1});
            }
        }

        int ans = INF;
        for (auto p : cur) {
            if (dp.find(p.first) == dp.end()) {
                dp[p.first] = p.second;
            } else {
                dp[p.first] = min(dp[p.first], p.second);
            }
            if (comp(p.first)) {
                ans = min(ans, p.second);
            }
        }

        if (ans != INF) {
            cout << ans << '\n';
            return 0;
        }
    }

    cout << "-1\n";
    return 0;
}
