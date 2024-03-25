#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

using ld = long double;
using ll = long long;

constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;

int main() {
    int m, n, k, s;
    cin >> m >> n >> k >> s;

    vector<ld> pts;
    pts.reserve(m + n);
    for (int i = 0; i < m; i++) {
        ld x;
        cin >> x;
        pts.push_back(x);
    }
    for (int i = 0; i < n; i++) {
        ld x;
        cin >> x;
        pts.push_back(x);
    }

    sort(pts.begin(), pts.end());

    vector<ld> psum(m + n + 1);
    vector<ld> psum_sq(m + n + 1);

    for (int i = 0; i < m + n; i++) {
        psum[i + 1] = psum[i] + pts[i];
        psum_sq[i + 1] = psum_sq[i] + pts[i] * pts[i];
    }

    vector dp(m + n + 1, vector<ld>(k + 1, INFLL));
    dp[0][0] = 0;

    for (int r = 1; r <= m + n; r++) {
        for (int used = 1; used <= k; used++) {
            for (int l = 0; l < r; l++) {
                auto loc = (psum[r] - psum[l]) / (r - l);
                auto cost = (psum_sq[r] - psum_sq[l]) 
                    - 2 * loc * (psum[r] - psum[l])
                    + (r - l) * loc * loc;
                dp[r][used] = min(dp[r][used], dp[l][used - 1] + cost);
            }
        }
    }

    auto ans = *min_element(dp.back().begin(), dp.back().end());
    ans += (m + n) * (s / 2.0) * (s / 2.0);

    cout << fixed << setprecision(15);
    cout << ans << '\n';

    return 0;
}
