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
#define MAXN 1000

using namespace std;

int n;
ll x;
ll nums[MAXN];
map<ll, vector<pair<int, int>>> m;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (m.count(nums[i] + nums[j])) {
                m[nums[i] + nums[j]].push_back({i, j});
            } else {
                m[nums[i] + nums[j]] = {{i, j}};
            }
        }
    }

    for (auto v : m) {
        for (auto p : v.second) {
            ll c = x - v.first;
            if (m.count(c)) {
                for (auto y : m[c]) {
                    set<int> s = {p.first, p.second, y.first, y.second};
                    if (s.size() == 4) {
                        for (int i : s) {
                            cout << i + 1 << ' ';
                        } cout << '\n';
                        return 0;
                    }
                }
            }
        }
    }

    cout << "IMPOSSIBLE\n";

    return 0;
}
