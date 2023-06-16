/*
 * Using DFS, we can figure out which numbers we need to rotate in order to fix certain groups. We can then
 * use bitmask DP to figure out if we can solve the full set by iterating over the submasks of each mask and 
 * checking if the submask and its complement both are solvable.
 */
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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int k;
vector<int> nums[15];
map<int, bool> used;
map<int, int> loc;
ll sum[15];
int cnt[15];
ll to_get;

bool possible[1 << 15];
vector<array<int, 3>> how_do[1 << 15];

bool dfs(int idx, int num, int start, vector<int> &vals, vector<int> &grps) {
    cnt[idx]++;
    used[num] = true;
    vals.push_back(num);
    grps.push_back(idx);

    if (cnt[idx] == 2) {
        return false;
    }

    ll needed = to_get - (sum[idx] - num);

    if (loc.find(needed) == loc.end()) {
        return false;
    }

    int new_idx = loc[needed];

    if (needed == start) {
        return true;
    } else if (used[needed]) {
        return false;
    }

    return dfs(new_idx, needed, start, vals, grps);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> k;
    for (int i = 0; i < k; i++) {
        int n; cin >> n;
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            nums[i].push_back(x);
            to_get += x;
            sum[i] += x;
            loc[x] = i;
        }

        sort(nums[i].begin(), nums[i].end());
    }

    if (to_get % k != 0) {
        cout << "No\n";
        return 0;
    }

    to_get /= k;

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < (int)(nums[i].size()); j++) {
            vector<int> vals;
            vector<int> grps;

            vals.reserve(15);
            grps.reserve(15);

            fill(cnt, cnt + 15, 0);
            used.clear();
            bool res = dfs(i, nums[i][j], nums[i][j], vals, grps);

            if (res) {
                int mask = 0;
                for (int i : grps) {
                    mask += 1 << i;
                }

                vector<int> orig = grps;
                rotate(grps.begin(), grps.end() - 1, grps.end());

                vector<array<int, 3>> sol;
                for (int i = 0; i < (int)(vals.size()); i++) {
                    sol.push_back({orig[i], vals[i], grps[i]});
                }

                possible[mask] = true;
                how_do[mask] = sol;
            }
        }
    }

    for (int m = 1; m < (1 << k); m++) {
        for (int s = m; s > 0; s = (s - 1) & m) {
            if (possible[s] && possible[m ^ s]) {
                possible[m] = true;
                how_do[m] = how_do[s];
                for (auto p : how_do[m ^ s]) {
                    how_do[m].push_back(p);
                }
                break;
            }
        }
    }

    int res = (1 << k) - 1;
    if (possible[res]) {
        cout << "Yes\n";
        sort(how_do[res].begin(), how_do[res].end());
        for (auto [_, val, loc]  : how_do[res]) {
            cout << val << ' ' << loc + 1 << '\n';
        }
    } else {
        cout << "No\n";
    }

    return 0;
}
