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

vector<int> comp_greedy_len(const vector<int> &p) {
    int n = p.size();
    vector<pair<int, int>> ord;
    for (int i = 0; i < n; i++) {
        ord.push_back({p[i], i});
    }

    sort(ord.begin(), ord.end());

    set<pair<int, int>> s;
    vector<int> ans(n);
    for (auto [v, i] : ord) {
        auto pp = pair{i, v};
        s.insert(pp);
        while (true) {
            auto it = s.find(pp);
            if (next(it) == s.end()) {
                break;
            }
            s.erase(next(it));
        }

        ans[v] = s.size();
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<int> p(n);
    for (auto &x : p) {
        cin >> x;
        x--;
    }

    auto greedy_up = comp_greedy_len(p);

    auto p_flip = p;
    for (int i = 0; i < n; i++) {
        p_flip[i] = n - p[i] - 1;
    }

    auto greedy_down = comp_greedy_len(p_flip);
    reverse(greedy_down.begin(), greedy_down.end());

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, greedy_up[i] + greedy_down[i] - 1);
    }

    cout << ans << '\n';


    return 0;
}
