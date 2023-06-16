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

void solve() {
    int n; cin >> n;
    vector<array<int, 2>> ppl(n);
    vector<array<int, 2>> sweet(n + 1);

    for (int i = 0; i < n; i++) {
        cin >> ppl[i][0] >> ppl[i][1];
    }

    for (int i = 0; i < n + 1; i++) {
        cin >> sweet[i][0] >> sweet[i][1];
    }

    vector<int> ord;
    for (int i = 0; i < n; i++) ord.push_back(i);

    vector<int> used(n + 1);
    function<vector<int>(int)> check = [&](int x) -> vector<int> {
        double min_d = INFLL;
        vector<int> best;

        for (int i = 0; i < n + 1; i++) {
            if (!used[i]) {
                double d = hypot(sweet[i][0] - ppl[x][0], sweet[i][1] - ppl[x][1]);
                if (d < min_d) {
                    min_d = d;
                    best = {i};
                } else if (fabs(min_d - d) <= eps) {
                    best.push_back(i); 
                }
            }

            if (x == n - 1) {
                if (best.size() == 1 && best[0] == 0) {
                    return {};
                } else {
                    return {ord[x + 1], 
                }
            }

            for (int y : best) {
                if (y != 0) {
                    used[y] = true;

                    auto res = check(x + 1);
                    if (!res.empty()) {
                        res.push_back({x + 1, y});
                        return res;
                    }

                    used[x] = false;
                }
            }
        }
    };

    do {
        if (!res.empty()) {
            cout << "POSSIBLE\n";
            for (auto [a, b] : res) {
                cout << a << ' ' << b << '\n';
            }
            return;
        }
    } while (next_permutation(ord.begin(), ord.end()));

    cout << "IMPOSSIBLE\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
