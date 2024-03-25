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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

#define sz(x) (int) x.size()

struct FT {
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif) {
        for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
    }
    ll query(int pos) {
        ll res = 0;
        for(; pos > 0; pos &= pos - 1) res += s[pos-1];
        return res;
    }
    int lower_bound(ll sum) {
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
                pos += pw, sum -= s[pos-1];
        }
        return pos;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    n /= 2;

    FT in(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        in.update(i, 1);
    }

    vector<int> p1(n), p2(n);
    for (int i = 0; i < n; i++) {
        cin >> p1[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> p2[i];
    }

    vector<int> ans1(n), ans2(n);

    for (int i = 0; i < n; i++) {
        ans1[i] = in.lower_bound(p1[i]);
        in.update(ans1[i], -1);
        ans2[i] = in.lower_bound(p2[i]);
        in.update(ans2[i], -1);
    }
    
    for (int i = 0; i < n; i++) {
        cout << ans1[i] + 1 << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans2[i] + 1 << ' ';
    }
    cout << '\n';

    return 0;
}
