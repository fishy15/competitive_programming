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
#include <bitset>

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

template<int D>
void solve(int n, int d) {
    if (d >= D) {
        solve<min(2*D, 2001)>(n, d);
        return;
    }

    vector<int> l(n);
    rep(i, 0, n) {
        cin >> l[i];
    }

    sort(all(l));

    // no way of getting a smaller diameter
    if (l[n - 2] + l[n - 1] > d) {
        cout << "No\n";
        return;
    }

    // check if it is possible to put l[-1] as the final segment
    bitset<D> poss;
    poss[0] = 1;

    rep(i, 0, n-1) {
        poss |= poss << l[i];
    }

    auto biggest = l.back();
    if (poss[d - biggest]) {
        cout << "Yes\n";
        return;
    }

    // see if we can make path d and split 
    if (poss[d]) {
        // poss[sum][diff]
        vector<bitset<D>> poss2(d+1);
        poss2[0][0] = 1;

        rep(i, 0, n-1) {
            for (int cur = d - l[i]; cur >= 0; cur--) {
                poss2[cur + l[i]] |= poss2[cur] | (poss2[cur] << l[i]);
            }
        }

        for (int first = 0; first <= d; first++) {
            int second = d - first;
            if (poss2[d][first]) {
                if (max(first, second) + biggest <= d) {
                    cout << "Yes\n";
                    return;
                }
            }
        }
        cout << endl;
    }

    cout << "No\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        int n, d;
        cin >> n >> d;
        solve<1>(n, d);
    }

    return 0;
}
