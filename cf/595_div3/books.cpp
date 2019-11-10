// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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
#define MAXN 1000000

using namespace std;

int n;
int cur;
int depth;
vector<int> nums;
vector<int> dist;

int dfs(int pos, vector<int> &v) {
    if (v[pos] == cur) {
        dist[pos] = depth;
        return depth;
    }

    depth++;
    return dist[pos] = dfs(v[pos], v);
}

void solve() {
    cin >> n;
    nums = {};
    dist = {};

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x - 1);
        dist.push_back(-1);
    }

    for (int i = 0; i < n; i++) {
        if (dist[i] == -1) {
            cur = i;
            depth = 1;
            dfs(i, nums);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << dist[i] << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int q; cin >> q;

    while (q--) {
        solve();
    }

    return 0;
}
