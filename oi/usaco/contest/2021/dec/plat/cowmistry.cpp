#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

int n, k;
int max_r;
int ans;
vector<int> ok;

int isect(int a, int b, int l, int r) {
    if (a > r || b < l) return 0;
    return max(b, r) - min(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    if (((k + 1) & (-k - 1)) == 0) {
        vector<pair<int, int>> x;
        for (int i = 0; i < n; i++) {
            int l, r; cin >> l >> r;
            x.push_back({l, r});
            max_r = max(max_r, r);
        }

        int m = 0;
        while (m * (k + 1) <= max_r) {
            int start = m * (k + 1);
            int end = (m + 1) * (k + 1) - 1;
            for (int i = 0; i < n; i++) {
                ll sz = isect(x[i].first, x[i].second, start, end);
                ans += sz * (sz - 1) * (sz - 2) / 6 % MOD;
                if (ans >= MOD) ans -= MOD);
            }
        }


    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        for (int i = l; i <= r; i++) ok.push_back(i);
    }

    int sz = ok.size();

    for (int a = 0; a < sz; a++) {
        for (int b = a + 1; b < sz; b++) {
            if ((ok[a] ^ ok[b]) > k) continue;
            for (int c = b + 1; c < sz; c++) {
                ans += 1 - ((ok[a] ^ ok[c]) > k || (ok[b] ^ ok[c]) > k);
            }
        }
    }

    cout << ans << '\n';
    
    return 0;
}
