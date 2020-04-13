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
#define MAXN 200000

using namespace std;

int ans[MAXN + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<pair<int, int>> ord;
    for (int i = 1; i <= n; i++) {
        int a, b; cin >> a >> b;
        ord.push_back({a, i});
        ord.push_back({b + 1, -i});
    }

    sort(ord.begin(), ord.end());

    set<int> used;
    set<int> empty;
    int k = 0;

    for (auto p : ord) {
        if (p.second > 0) {
            if (empty.empty()) {
                k++;
                used.insert(k);
                ans[p.second] = k;
            } else {
                int v = *empty.begin();
                empty.erase(v);
                ans[p.second] = v;
                used.insert(v);
            }
        } else {
            used.erase(ans[-p.second]);
            empty.insert(ans[-p.second]);
        }
    }

    cout << k << '\n';
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    } cout << '\n';
    return 0;
}
