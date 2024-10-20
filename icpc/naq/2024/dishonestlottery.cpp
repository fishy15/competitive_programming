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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    map<int, int> counts;
    rep(i, 0, 50*n) {
        int x;
        cin >> x;
        counts[x]++;
    }

    vector<int> ans;
    for (auto [val, cnt] : counts) {
        if (cnt > 2*n) {
            ans.push_back(val);
        }
    }

    if (ans.empty()) {
        cout << "-1\n";
    } else {
        for (auto x : ans) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}
