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
#define MAXN 100010

using namespace std;

int n, q;
int nums[MAXN];
int pre[MAXN];
vector<pair<int, int>> add[MAXN];
vector<pair<int, int>> rem[MAXN];
multiset<pair<int, int>> cur;
int t;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        if (nums[i]) {
            pre[i]++;
            pre[i + 1]--;
            add[i].push_back({t, nums[i]});
            rem[i + 1].push_back({t, nums[i]});
            t++;
        }
    }

    for (int i = 0; i < q; i++) {
        int l, r, x; cin >> l >> r >> x;
        pre[l]++;
        pre[r + 1]--;
        add[l].push_back({t, x});
        rem[r + 1].push_back({t, x});
        t++;
    }

    for (int i = 1; i <= n; i++) {
        pre[i] += pre[i - 1];
        for (auto &p : add[i]) {
            cur.insert(p);
        } 
        for (auto &p : rem[i]) {
            cur.erase(cur.find(p));
        }
        if (pre[i] % 2 == 0) {
            cout << 0 << ' ';
        } else {
            cout << cur.rbegin()->second << ' ';
        }
    }

    cout << '\n';

    return 0;
}
