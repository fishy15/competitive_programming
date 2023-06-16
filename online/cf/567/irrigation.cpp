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
#define MAXN 500010

using namespace std;

int n, m, q;
int cnt[MAXN];
vector<int> cur_cnt[MAXN];
pair<ll, int> qry[MAXN];
int ans[MAXN];

struct BIT {
    int bit[MAXN];
    
    void upd(int x, int v) {
        while (x < MAXN) {
            bit[x] += v;
            x += x & -x;
        }
    }

    int qry(int x) {
        int res = 0;
        while (x) {
            res += bit[x];
            x -= x & -x;
        }
        return res;
    }

    int search(int x) {
        int sum = 0;
        int cur = 0;
        for (int i = 19; i >= 0; i--) {
            if (cur + (1 << i) < MAXN && sum + bit[cur + (1 << i)] < x) {
                cur += 1 << i;
                sum += bit[cur];
            }
        }
        return cur + 1;
    }
} bit;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> m >> q;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    for (int i = 1; i <= m; i++) {
        cur_cnt[cnt[i]].push_back(i);
    }

    for (int i = 0; i < q; i++) {
        cin >> qry[i].first;
        qry[i].first -= n;
        qry[i].second = i;
    }
    
    sort(qry, qry + q);
    int qpos = 0;
    ll done = 0;
    ll tot = 0;

    for (int i = 0; i <= n; i++) {
        tot += cur_cnt[i].size();
        for (int x : cur_cnt[i]) {
            bit.upd(x, 1);
        }
        while (qpos < q && qry[qpos].first <= done + tot) {
            ans[qry[qpos].second] = bit.search(qry[qpos].first - done);
            qpos++;
        }
        done += tot;
    }

    while (qpos < q) {
        ans[qry[qpos].second] = bit.search((qry[qpos].first - done) % m);
        qpos++;
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
