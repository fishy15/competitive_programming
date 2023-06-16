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
#define MAXN 1000000

using namespace std;

int n;
map<int, int> pos;
vector<pair<int, int>> mov;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        mov.push_back({b, a});
    }

    sort(mov.begin(), mov.end());

    int ans = 0;
    for (auto p : mov) {
        swap(p.first, p.second);
        auto it = pos.upper_bound(p.first);
        int v = 0;
        if (it != pos.begin()) {
            it--;
            v = it->second;
        }
        pos[p.second] = max(ans, v + 1);
        ans = max(ans, v + 1);
    }

    cout << ans << '\n';

    return 0;
}
