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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll a, b;
    int g;
    cin >> a >> b >> g;

    vector<int> diffs;
    int carry = 0;
    ll common = 0;
    for (int i = 0; i <= 60; i++) {
        if ((b >> i) & 1) {
            // at least one is set
            if ((a >> i) & 1) {
                // sum is 1
                if (carry == 0) {
                    // either one is set
                    diffs.push_back(i);
                    carry = 0;
                } else {
                    // both need to be set
                    common += 1LL << i;
                    carry = 1;
                }
            } else {
                if (carry == 0) {
                    // both need to be set
                    common += 1LL << i;
                    carry = 1;
                } else {
                    // either one is set
                    diffs.push_back(i);
                    carry = 1;
                }
            }
        } else {
            // both must be zero
            int a_set = (a >> i) & 1;
            if (a_set != carry) {
                cout << "0\n";
                if (g == 1) cout << "-1\n";
                return 0;
            }

            carry = 0;
        }
    }

    ll ans = 1;
    rep(_, 0, sz(diffs)) ans *= 2;

    ll diff = 1LL << diffs.back();
    rep(i, 0, sz(diffs) - 1) {
        diff -= 1LL << diffs[i];
    }

    cout << ans << '\n';
    if (g == 1) cout << diff << '\n';

    return 0;
}
