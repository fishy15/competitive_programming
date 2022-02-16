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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 500010

using namespace std;

int n, k;
int nums[MAXN];
vector<int> pos[MAXN];
int dist[MAXN];
ll dist2[MAXN];

int nxt(int i) {
    return (i + dist[i]) % n;
}

ll ckmin(ll &a, ll b) {
    return a = min(a, b);
}

int get_dist(int a, int b) {
    return (b - a + n) % n;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        pos[nums[i]].push_back(i);
    }

    for (int i = 0; i < n; i++) {
        int x = nums[i];
        if (x < k) {
            auto it = upper_bound(pos[x + 1].begin(), pos[x + 1].end(), i);
            if (it == pos[x + 1].end()) {
                dist[i] = get_dist(i, pos[x + 1][0]);
            } else {
                dist[i] = get_dist(i, *it);
            }
        }
    }

    fill(dist2, dist2 + n, INFLL);
    for (int i = 1; i < k; i++) {
        for (int j : pos[i]) {
            if (i == 1) {
                dist2[j] = 1;
            }

            ckmin(dist2[nxt(j)], dist2[j] + dist[j]);
        }

        int pre = -1;
        for (int j : pos[i + 1]) {
            if (pre != -1) {
                ckmin(dist2[j], dist2[pre] + get_dist(pre, j));
                pre = j;
            }
        }
        for (int j : pos[i + 1]) {
            if (pre != -1) {
                ckmin(dist2[j], dist2[pre] + get_dist(pre, j));
                pre = j;
            }
        }
        for (int j : pos[i + 1]) {
            if (pre != -1) {
                ckmin(dist2[j], dist2[pre] + get_dist(pre, j));
                pre = j;
            }
        }
    }

    ll ans = INFLL;
    for (int i : pos[k]) {
        ckmin(ans, dist2[i]);
    }

    cout << ans << '\n';


    return 0;
}
