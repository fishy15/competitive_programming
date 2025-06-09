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

constexpr int MAXN = 500'000;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, d;
    cin >> n >> d;

    vector<int> items(n);
    rep(i, 0, n) {
        cin >> items[i];
    }

    vector<bool> can_make(MAXN + 1);
    can_make[0] = 1;
    for (auto x : items) {
        for (int i = MAXN - x; i >= 0; i--) {
            can_make[i + x] = can_make[i + x] || can_make[i];
        }
    }

    deque<pair<int, int>> q;
    // location, steps
    q.push_back({0, 0});

    pair<int, int> ans = {0, 0};
    for (int i = 1; i <= MAXN; i++) {
        while (!q.empty() && q.front().first < i - d) {
            q.pop_front();
        }

        if (!q.empty() && can_make[i]) {
            pair<int, int> steps = {i, q.front().second + 1};
            ans = steps;
            q.push_back(steps);
        }
    }

    cout << ans.first << ' ' << ans.second << '\n';

    return 0;
}
