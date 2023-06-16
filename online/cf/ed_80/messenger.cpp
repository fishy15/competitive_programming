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
#define MAXN 300000

using namespace std;

int n, m;
vector<int> nums;
int min_ans[MAXN + 1];
int max_ans[MAXN + 1];
vector<int> pos[MAXN + 1];
vector<array<int, 3>> q;
int last[MAXN + 1];

int bit[2 * MAXN + 10];
void add(int x, int v) {
    while (x < 2 * MAXN + 10) {
        bit[x] += v;
        x += x & -x;
    }
}

int query(int x) {
    int ans = 0;
    while (x > 0) {
        ans += bit[x];
        x -= x & -x;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = n; i > 0; i--) {
        nums.push_back(i);
        min_ans[i] = i;
        max_ans[i] = i;
        add(n - i + 1, 1);
    }

    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        min_ans[x] = 1;
        nums.push_back(x);
    }

    for (int i = 0; i < n + m; i++) {
        if (last[nums[i]]) {
            q.push_back({last[nums[i]], i + 1, nums[i]});
        }
        last[nums[i]] = i + 1;
    }

    sort(q.begin(), q.end(), [&](const array<int, 3> &a1, const array<int, 3> &a2) -> bool {
        if (a1[1] == a2[1]) {
            return a1 < a2;
        }
        return a1[1] < a2[1];
    });

    for (auto qq : q) {
        int v = query(qq[1]) - query(qq[0] - 1);
        add(qq[1], 1);
        add(qq[0], -1);
        max_ans[qq[2]] = max(max_ans[qq[2]], v);
    }

    for (int i = 1; i <= n; i++) {
        int v = query(n + m) - query(last[i] - 1);
        max_ans[i] = max(max_ans[i], v);
    }

    for (int i = 1; i <= n; i++) {
        cout << min_ans[i] << ' ' << max_ans[i] << '\n';
    }

    return 0;
}
