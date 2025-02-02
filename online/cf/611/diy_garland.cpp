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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

pair<vector<pair<int,int>>, int> pruefer(const vector<int> &nums) {
    int n = sz(nums) + 1;
    vector<int> deg(n, 1);
    for (auto v : nums) {
        deg[v]++;
    }

    priority_queue<int, vector<int>, greater<>> leaves;
    vector<pair<int, int>> edges;
    rep(v, 0, n) {
        if (deg[v] == 1) {
            leaves.push(v);
        }
    }

    for (auto v : nums) {
        int leaf = leaves.top();
        leaves.pop();

        edges.push_back({v, leaf});
        deg[v]--;
        if (deg[v] == 1) {
            leaves.push(v);
        }
    }

    return {edges, leaves.top()};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> nums(n-1);
    rep(i, 0, n-1) {
        cin >> nums[i];
        nums[i]--;
    }

    reverse(all(nums));
    auto [tree, root] = pruefer(nums);

    cout << root+1 << '\n';
    for (auto [a, b] : tree) {
        cout << a+1 << ' ' << b+1 << '\n';
    }


    return 0;
}
