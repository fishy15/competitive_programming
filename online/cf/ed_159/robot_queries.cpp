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

pair<int, int> dir(char c) {
    if (c == 'U') return {0, 1};
    if (c == 'D') return {0, -1};
    if (c == 'L') return {-1, 0};
    return {1, 0};
}

pair<int, int> operator+(const pair<int, int> a, const pair<int, int> b) {
    return {a.first + b.first, a.second + b.second};
}

pair<int, int> operator-(const pair<int, int> a, const pair<int, int> b) {
    return {a.first - b.first, a.second - b.second};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    vector<array<int, 4>> qry(q);

    for (auto &[x, y, l, r] : qry) {
        cin >> x >> y >> l >> r;
        l--;
        r--;
    }

    map<pair<int, int>, set<int>> wants;
    for (int i = 0; i < q; i++) {
        auto [x, y, l, r] = qry[i];
        wants[{x, y}].insert(i);
    }

    vector<bool> ans(q);
    pair<int, int> final_loc;
    vector<pair<int, int>> where_at(n+1);

    auto process_front = [&] {
        auto front_wants = wants;
        vector<vector<int>> end_at(n);
        for (int i = 0; i < q; i++) {
            auto [x, y, l, r] = qry[i];
            end_at[l].push_back(i);
        }

        pair<int, int> loc;
        for (int i = 0; i < n; i++) {
            if (front_wants.count(loc)) {
                for (auto x : front_wants[loc]) {
                    ans[x] = true;
                }
                front_wants.erase(loc);
            }

            for (auto idx : end_at[i]) {
                auto [x, y, l, r] = qry[idx];
                front_wants[{x, y}].erase(idx);
            }

            loc = loc + dir(s[i]);
            where_at[i+1] = loc;
        }

        final_loc = loc;
    };

    auto process_back = [&] {
        auto back_wants = wants;
        vector<vector<int>> end_at(n);
        for (int i = 0; i < q; i++) {
            auto [x, y, l, r] = qry[i];
            end_at[r].push_back(i);
        }

        pair<int, int> loc = final_loc;
        for (int i = n - 1; i >= 0; i--) {
            if (back_wants.count(loc)) {
                for (auto x : back_wants[loc]) {
                    ans[x] = true;
                }
                back_wants.erase(loc);
            }

            for (auto idx : end_at[i]) {
                auto [x, y, l, r] = qry[idx];
                back_wants[{x, y}].erase(idx);
            }

            loc = loc - dir(s[i]);
        }
    };

    auto process_mid = [&] {
        map<pair<int, int>, set<int>> mid_wants;
        vector<pair<int, int>> rev_wants(q);
        vector<vector<int>> end_at(n+1);
        vector<vector<int>> begin_at(n+1);
        for (int i = 0; i < q; i++) {
            auto [x, y, l, r] = qry[i];
            begin_at[l].push_back(i);
            end_at[r].push_back(i);

            auto offset_from_l = pair{x, y} - where_at[l];
            auto offset_from_r = where_at[r+1] - offset_from_l;
            rev_wants[i] = offset_from_r;
        }

        pair<int, int> loc = final_loc;
        for (int i = n - 1; i >= 0; i--) {
            for (auto idx : end_at[i]) {
                mid_wants[rev_wants[idx]].insert(idx);
            }

            loc = loc - dir(s[i]);

            if (mid_wants.count(loc)) {
                for (auto x : mid_wants[loc]) {
                    ans[x] = true;
                }
                mid_wants.erase(loc);
            }

            for (auto idx : begin_at[i]) {
                mid_wants[rev_wants[idx]].erase(idx);
            }
        }
    };

    process_front();
    process_back();
    process_mid();

    for (auto x : ans) {
        if (x) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
