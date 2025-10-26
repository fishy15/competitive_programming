#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    map<string, array<int, 3>> count;
    int tot = 0;
    rep(i, 0, n) {
        string mat, typ;
        int cnt;
        cin >> mat >> typ >> cnt;
        if (typ == "left") {
            count[mat][0] += cnt;
        } else if (typ == "right") {
            count[mat][1] += cnt;
        } else {
            count[mat][2] += cnt;
        }
        tot += cnt;
    }

    int ans = 0;
    int impossible_cnt = 0;
    for (auto [s, info] : count) {
        auto [l, r, a] = info;
        if (a == 0) {
            if (l > 0 && r > 0) {
                ans += max(l, r);
            } else {
                impossible_cnt++;
                ans += l + r + a;
            }
        } else if (a == 1) {
            if (l == 0 && r == 0) {
                impossible_cnt++;
                ans += l + r + a;
            } else {
                ans += max(l, r);
            }
        } else {
            // always possible
            ans += max({l, r, 1});
        }
    }

    ans += 1;
    if (impossible_cnt < sz(count)) {
        cout << ans << '\n';
    } else {
        cout << "impossible\n";
    }

    return 0;
}

