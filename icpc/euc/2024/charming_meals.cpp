#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    rep(i, 0, n) {
        cin >> b[i];
    }

    sort(all(a));
    sort(all(b));

    // lower on a, higher on b
    int ans = 0;
    rep(sp, 0, n) {
        int worst = 0x3f3f3f3f;
        rep(i, 0, sp) {
            worst = min(worst, abs(a[i] - b[n - sp + i]));
        }
        rep(i, sp, n) {
            worst = min(worst, abs(a[i] - b[i - sp]));
        }
        ans = max(ans, worst);
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

}

