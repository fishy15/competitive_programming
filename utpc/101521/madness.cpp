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
#define MAXN 1000000

using namespace std;

int q;
int len = 1;
vector<ll> psum = {0};
vector<ll> psq = {0};

pair<ld, ld> qry(ll t) {
    ll sum = psum.back() - psum[len - t - 1];
    ll ssum = psq.back() - psq[len - t - 1];

    ld avg = (ld) sum / t;
    ld sigma_x = sqrt(t * avg * avg - 2 * sum * avg + ssum) / t;
    return {avg - 2 * sigma_x, avg + 2 * sigma_x};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> q;
    cout << fixed << setprecision(10) << '\n';
    while (q--) {
        char t; cin >> t;
        if (t == 'R') {
            int x; cin >> x;
            psum.push_back(psum.back() + x);
            psq.push_back(psq.back() + x * x);
            len++;
        } else {
            int x; cin >> x;
            auto p = qry(x);
            cout << p.first << ' ' << p.second << '\n';
        }
    }

    return 0;
}
