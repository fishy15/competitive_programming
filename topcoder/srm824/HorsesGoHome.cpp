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

struct HorsesGoHome {
    array<int, 8> dx = {{2, 2, 1, -1, -2, -2, -1, 1}};
    array<int, 8> dy = {{-1, 1, 2, 2, 1, -1, -2, -2}};

    int calc_d(int x, int y) {
        int res = INF;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                res = min(res, abs(x - i) + abs(y - j));
            }
        }

        return (res + 2) / 3;
    }

    vector<int> solve(int x, int y) {
        vector<int> ans(1);

        int cur_d = calc_d(x, y);
        ans[0] = cur_d;

        if (ans[0] > 500) {
            return ans;
        }

        while (cur_d > 0) {
            pair<int, int> best;
            int d = INF;

            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                int nd = calc_d(nx, ny);
                if (nd < d) {
                    best = {nx, ny};
                    d = nd;
                }
            }

            ans.push_back(x);
            ans.push_back(y);
            ans.push_back(best.first);
            ans.push_back(best.second);

            x = best.first;
            y = best.second;
            cur_d = d;
        }

        return ans;
    }

    vector<int> move(vector<int> hr, vector<int> hc) {
        int n = hr.size();

        vector<int> ans(1);
        for (int i = 0; i < n; i++) {
            auto res = solve(hr[i], hc[i]);

            ans[0] += res[0];

            if (ans[0] > 500) continue;

            int sz = res.size();
            for (int i = 1; i < sz; i++) {
                ans.push_back(res[i]);
            }
        }

        if (ans[0] > 500) {
            return {ans[0]};
        } else {
            return ans;
        }
    }
};
