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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

optional<vector<array<int, 2>>> split_reqs(vector<array<int, 2>> reqs) {
    vector<array<int, 2>> res = {{2, 3}};
    int cur_cnt = 3;
    for (auto [i, c] : reqs) {
        auto last = res.back();
        int idx_d = i - last[0];
        int inc = c - cur_cnt;

        if (idx_d < inc) {
            return {};
        }

       res.push_back({last[0] + inc, inc});
       res.push_back({i, 0});
       cur_cnt = c;
    }

    return vector<array<int, 2>>(res.begin() + 1, res.end());
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<array<int, 2>> reqs(k);
    for (int i = 0; i < k; i++) {
        cin >> reqs[i][0];
        reqs[i][0]--;
    }

    for (int i = 0; i < k; i++) {
        cin >> reqs[i][1];
    }

    string begin = "abc";

    auto res = split_reqs(reqs);
    if (res) {
        reqs = *res;
        string s = "abc";

        char cur_c = 'd';
        int cc = 0;

        for (auto [i, c] : reqs) {
            if (c == 0) {
                while ((int) s.size() <= i) {
                    s += begin[cc % 3];
                    cc++;
                }
            } else {
                for (int j = 0; j < c; j++) {
                    s += cur_c;
                }
                cur_c++;
            }
        }

        while ((int) s.size() < n) {
            s += 'a';
        }

        cout << "YES\n";
        cout << s << '\n';
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
