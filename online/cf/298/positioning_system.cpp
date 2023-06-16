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
#define MAXN 200010

using namespace std;

int n, m;
int d[MAXN];
int cnt[MAXN];
ll ans;

void prefix_get() {
    int cur_val = 1;
    int idx = 2;
    while (idx < n && cnt[idx] >= cur_val) {
        cur_val = cnt[idx];
        cnt[idx]--;
        idx++;
    }
    ans += d[idx - 1] - d[1];
}

void suffix_get() {
    int cur_val = 1;
    int idx = n - 1;
    while (idx > 1 && cnt[idx] >= cur_val) {
        cur_val = cnt[idx];
        cnt[idx]--;
        idx--;
    }
    ans += d[n] - d[idx + 1];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    if (n == 2) {
        cout << (ll) (cnt[1] + cnt[2] - 1) * (d[2] - d[1]) << '\n';
        return 0;
    }

    if (cnt[1] == 0 && cnt[n] == 0) {
        for (int i = 1; i <= n; i++) {
            if (cnt[i] == 1 && cnt[i - 1] == 1) {
                ans += d[i] - d[i - 1];
            }
        }
        cout << ans << '\n';
        return 0;
    }

    int to_rem = cnt[1] + cnt[n] - 1;
    for (int i = 2; i < n; i++) {
        cnt[i] -= to_rem;
    }

    ans += (ll) (d[n] - d[1]) * to_rem;

    if (cnt[1] == cnt[n]) {
        if (all_of(cnt + 2, cnt + n, [](int x) { return x == 1; })) {
            int max_diff = 0;
            int min_diff = INF;

            for (int i = 1; i < n; i++) {
                int diff = d[i + 1] - d[i];
                max_diff = max(max_diff, diff);
                min_diff = min(min_diff, diff);
            }

            if (max_diff != min_diff) {
                cout << "-1\n";
            } else {
                ans += d[n - 1] - d[1];
                cout << ans << '\n';
            }
        } else {
            prefix_get();
            suffix_get();
            cout << ans << '\n';
        }
    } else if (cnt[1] > cnt[n]) {
        prefix_get();
        prefix_get();
        cout << ans << '\n';
    } else {
        suffix_get();
        suffix_get();
        cout << ans << '\n';
    }


    return 0;
}
