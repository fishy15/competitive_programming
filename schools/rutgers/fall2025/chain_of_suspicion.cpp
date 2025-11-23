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

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    char cur = 's';
    int len = 0;
    vector<int> groups;
    for (auto c : s) {
        if (c != cur) {
            groups.push_back(len);
            cur = c;
            len = 1;
        } else {
            len++;
        }
    }

    groups.push_back(len);
    if (cur != 's') {
        groups.push_back(0);
    }

    pair<int, int> last_bounds = {-1, -1};
    int chars_so_far = 0;
    int last_ans = 0;
    int best_ans = 0;
    for (int i = 1; i < sz(groups); i += 2) {
        chars_so_far += groups[i - 1];

        // now, its index of the first match
        if (groups[i - 1] >= groups[i] && groups[i] <= groups[i + 1]) {
            int l = chars_so_far - groups[i];
            int r = chars_so_far + 2 * groups[i];
            int ans = r - l;
            if (l == last_bounds.second) {
                ans += last_ans;
            }

            last_bounds = {l, r};
            last_ans = ans;
            best_ans = max(best_ans, ans);
        } else {
            last_bounds = {-1, -1};
            last_ans = 0;
        }
        
        chars_so_far += groups[i];
    }

    cout << best_ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
