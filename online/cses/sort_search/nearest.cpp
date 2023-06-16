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

int n;
int nums[MAXN];
int ans[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    vector<pair<int, int>> pos;
    set<int> cur;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        pos.push_back({nums[i], i});
    }

    sort(pos.begin(), pos.end(), [](const pair<int, int> &p1, const pair<int, int> &p2) {
        if (p1.first == p2.first) return p1.second > p2.second;
        return p1 < p2;
    });

    for (int i = 0; i < n; i++) {
        auto it = cur.lower_bound(pos[i].second);
        if (it == cur.begin()) {
            ans[pos[i].second] = 0;
        } else {
            it--;
            ans[pos[i].second] = *it + 1;
        }
        cur.insert(pos[i].second);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    } cout << '\n';

    return 0;
}
