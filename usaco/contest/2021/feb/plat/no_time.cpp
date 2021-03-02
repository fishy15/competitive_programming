#include <iostream>
#include <vector>
#include <array>

#define MAXN 200010

using namespace std;

int n, q;
int nums[MAXN];
int ans[MAXN];
int min_cost[MAXN];

int find(int idx, vector<array<int, 3>> &dec, bool less_eq) {
    int lo = 0;
    int hi = dec.size() - 1;
    int ans = 0;
    while (lo <= hi) {
        int m = (lo + hi) / 2;
        bool cmp = less_eq ? idx <= dec[m][1] : idx >= dec[m][1];
        if (cmp) {
            ans = m;
            lo = m + 1;
        } else {
            hi = m - 1;
        }
    }
    return ans;
}

void solve(int l, int r, const vector<array<int, 3>> &qry) {
    if (qry.empty()) return;

    if (l == r) {
        for (auto q : qry) {
            ans[q[2]] = 1;
        }
        return;
    }

    int m = (l + r) / 2;
    vector<array<int, 3>> left, right, cur;
    for (auto q : qry) {
        if (q[1] <= m) {
            left.push_back(q);
        } else if (q[0] > m) {
            right.push_back(q);
        } else {
            cur.push_back(q);
        }
    }

    solve(l, m, left);
    solve(m + 1, r, right);

    // solve the main part
    vector<int> stack;
    for (int i = m; i >= l; i--) {
        while (!stack.empty() && stack.back() > nums[i]) {
            stack.pop_back();
        }
        if (i == m) {
            min_cost[i] = 1;
            stack.push_back(nums[i]);
        } else {
            min_cost[i] = min_cost[i + 1];
            if (stack.empty() || stack.back() != nums[i]) {
                min_cost[i]++;
                stack.push_back(nums[i]);
            }
        }
    }

    stack.clear();
    for (int i = m + 1; i <= r; i++) {
        while (!stack.empty() && stack.back() > nums[i]) {
            stack.pop_back();
        }
        if (i == m + 1) {
            min_cost[i] = 1;
            stack.push_back(nums[i]);
        } else {
            min_cost[i] = min_cost[i - 1];
            if (stack.empty() || stack.back() != nums[i]) {
                min_cost[i]++;
                stack.push_back(nums[i]);
            }
        }
    }

    vector<array<int, 3>> left_dec, right_dec;
    for (int i = m; i >= l; i--) {
        if (left_dec.empty() || left_dec.back()[0] > nums[i]) {
            left_dec.push_back({nums[i], i, 0});
        }
    }

    for (int i = m + 1; i <= r; i++) {
        if (right_dec.empty() || right_dec.back()[0] > nums[i]) {
            right_dec.push_back({nums[i], i, 0});
        }
    }

    int l_idx = 0;
    int r_idx = 0;
    int l_sz = left_dec.size();
    int r_sz = right_dec.size();

    // calculate overlap
    while (l_idx < l_sz || r_idx < r_sz) {
        if (l_idx == l_sz) {
            right_dec[r_idx][2] = r_idx ? right_dec[r_idx - 1][2] : 0;
            r_idx++;
        } else if (r_idx == r_sz) {
            left_dec[l_idx][2] = l_idx ? left_dec[l_idx - 1][2] : 0;
            l_idx++;
        } else {
            // case that both are ok
            if (left_dec[l_idx][0] == right_dec[r_idx][0]) {
                left_dec[l_idx][2] = l_idx ? left_dec[l_idx - 1][2] + 1 : 1;
                right_dec[r_idx][2] = r_idx ? right_dec[r_idx - 1][2] + 1 : 1;
                l_idx++;
                r_idx++;
            } else if (left_dec[l_idx][0] > right_dec[r_idx][0]) {
                left_dec[l_idx][2] = l_idx ? left_dec[l_idx - 1][2] : 0;
                l_idx++;
            } else {
                right_dec[r_idx][2] = r_idx ? right_dec[r_idx - 1][2] : 0;
                r_idx++;
            }
        }
    }

    for (auto [l, r, p] : cur) {
        ans[p] = min_cost[l] + min_cost[r];
        int l_loc = find(l, left_dec, true);
        int r_loc = find(r, right_dec, false);
        if (left_dec[l_loc][0] >= right_dec[r_loc][0]) {
            ans[p] -= left_dec[l_loc][2];
        } else {
            ans[p] -= right_dec[r_loc][2];
        }
    }

    cur = {};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<array<int, 3>> qry(q);
    for (int i = 0; i < q; i++) {
        cin >> qry[i][0] >> qry[i][1];
        qry[i][0]--;
        qry[i][1]--;
        qry[i][2] = i;
    }

    solve(0, n - 1, qry);

    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
