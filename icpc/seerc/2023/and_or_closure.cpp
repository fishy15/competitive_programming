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

int get(ll num, int index) {
    return (num >> index) & 1;
}

vector<int> get_important_indices(const vector<ll> &nums) {
    int n = nums.size();
    vector<int> index;

    // only want indices that can change, lowest in equivalence class
    for (int i = 0; i < 40; i++) {
        bool diff = false;
        for (int j = 0; j < n; j++) {
            if (get(nums[j], i) != get(nums[0], i)) {
                diff = true;
                break;
            }
        }

        if (diff) {
            bool same_as_other = false;
            for (int k = 0; k < i; k++) {
                bool diff_from_this = false;
                for (int j = 0; j < n; j++) {
                    if (get(nums[j], i) != get(nums[j], k)) {
                        diff_from_this = true;
                        break;
                    }
                }

                if (!diff_from_this) {
                    same_as_other = true;
                    break;
                }
            }

            if (!same_as_other) {
                index.push_back(i);
            }
        }
    }

    return index;
}

// constructs a dag between equivalence classes
// a -> b if a = 1 implies b = 1
vector<vector<int>> construct_dag(const vector<ll> &nums) {
    vector<int> index = get_important_indices(nums);

    vector<vector<int>> adj(index.size());
    for (int i = 0; i < (int) index.size(); i++) {
        for (int j = 0; j <  (int) index.size(); j++) {
            if (i == j) continue;
            int a = index[i];
            int b = index[j];

            bool edge = true;
            for (auto num : nums) {
                if (get(num, a) && !get(num, b)) {
                    edge = false;
                    break;
                }
            }

            if (edge) {
                // uses the compressed representations
                adj[i].push_back(j);
            }
        }
    }

    return adj;
}

vector<vector<bool>> get_reachability(const vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> deg(adj.size());
    vector reachable(n, vector<bool>(n));
    queue<int> q;

    vector<vector<int>> radj(n);
    for (int i = 0; i < n; i++) {
        deg[i] = adj[i].size();
        if (deg[i] == 0) {
            q.push(i);
        }

        for (auto e : adj[i]) {
            radj[e].push_back(i);
        }
    }

    while (!q.empty()) {
        auto v = q.front();
        q.pop();

        reachable[v][v] = true;
        for (auto e : adj[v]) {
            for (int i = 0; i < n; i++) {
                reachable[v][i] = reachable[v][i] || reachable[e][i];
            }
        }

        for (auto e : radj[v]) {
            deg[e]--;
            if (deg[e] == 0) {
                q.push(e);
            }
        }
    }

    return reachable;
}

vector<bool> mask_antichain(int start, int size, const vector<vector<bool>> &reachable) {
    vector<bool> res(1 << size);
    for (int m = 0; m < (1 << size); m++) {
        res[m] = true;
        for (int i = 0; i < size; i++) {
            if (!get(m, i)) continue;
            for (int j = i + 1; j < size; j++) {
                if (!get(m, j)) continue;
                if (reachable[i + start][j + start] || reachable[j + start][i + start]) {
                    res[m] = false;
                    goto done;
                }
            }
        }
done:
        continue;
    }

    return res;
}

vector<int> sos(int sz, const vector<bool> &mask_ok) {
    int n = 1 << sz;
    vector<int> res(mask_ok.size());
    for (int i = 0; i < n; i++) {
        res[i] = mask_ok[i] ? 1 : 0;
    }

    for (int i = 0; i < sz; i++) {
        for (int m = 0; m < n; m++) {
            if (m & (1 << i)) {
                res[m] += res[m ^ (1 << i)];
            }
        }
    }

    return res;
}

ll count_antichains(const vector<vector<int>> &adj) {
    int n = adj.size();
    auto reachable = get_reachability(adj);

    int first_sz = n / 2;
    int second_sz = n - n / 2;
    auto first_masks = mask_antichain(0, first_sz, reachable);
    auto second_masks = mask_antichain(n / 2, second_sz, reachable);
    auto second_sos = sos(second_sz, second_masks);

    ll ans = 0;
    for (int first_m = 0; first_m < (1 << first_sz); first_m++) {
        if (first_masks[first_m]) {
            int second_m = 0;
            for (int j = 0; j < second_sz; j++) {
                bool ok = true;
                for (int i = 0; i < first_sz; i++) {
                    if (get(first_m, i) && (reachable[i][n / 2 + j] || reachable[n / 2 + j][i])) {
                        ok = false;
                        break;
                    }
                }

                if (ok) {
                    second_m |= 1 << j;
                }
            }

            ans += second_sos[second_m];
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<ll> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    auto adj = construct_dag(nums);
    auto ans = count_antichains(adj);

    cout << ans << '\n';

    return 0;
}
