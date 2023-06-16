#include <iostream>
#include <vector>

#include "sorting.h"

using namespace std;

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
    int l = 0;
    int r = M;
    int ans = -1;

    auto check = [&](int m) {
        vector<int> nums(S, S + N);
        for (int i = 0; i < m; i++) {
            swap(nums[X[i]], nums[Y[i]]);
        }

        vector<bool> vis(N);
        int cycle_count = 0;

        for (int i = 0; i < N; i++) {
            if (!vis[i]) {
                cycle_count++;

                int cur = nums[i];
                while (cur != i) {
                    vis[cur] = true;
                    cur = nums[cur];
                }
            }
        }

        return N - cycle_count <= m;
    };

    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    vector<int> after_m(S, S + N);
    for (int i = 0; i < ans; i++) {
        swap(after_m[X[i]], after_m[Y[i]]);
    }

    vector<pair<int, int>> nums_to_swap;
    vector<bool> vis(N);

    for (int i = 0; i < N; i++) {
        if (!vis[i]) {
            int nxt = after_m[i];
            int pre = i;
            vis[i] = true;
            while (!vis[nxt]) {
                vis[nxt] = true;
                nums_to_swap.push_back({pre, nxt});
                pre = nxt;
                nxt = after_m[nxt];
            }
        }
    }

    while ((int) nums_to_swap.size() < ans) {
        nums_to_swap.push_back({0, 0});
    }

    vector<int> cur_p(S, S + N);
    vector<int> cur_inv(N);
    for (int i = 0; i < N; i++) {
        cur_inv[cur_p[i]] = i;
    }

    for (int i = 0; i < ans; i++) {
        // their swap
        auto t1 = cur_p[X[i]];
        auto t2 = cur_p[Y[i]];
        swap(cur_p[X[i]], cur_p[Y[i]]);
        swap(cur_inv[t1], cur_inv[t2]);

        // our swap
        auto [num1, num2] = nums_to_swap[i];
        auto idx1 = cur_inv[num1];
        auto idx2 = cur_inv[num2];

        P[i] = idx1;
        Q[i] = idx2;

        swap(cur_p[idx1], cur_p[idx2]);
        swap(cur_inv[num1], cur_inv[num2]);
    }

    return ans;
}
