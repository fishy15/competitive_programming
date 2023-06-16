// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n; cin >> n;
    ll p[2] = {0, 0};
    ll q[2] = {0, 0};
    
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        p[x % 2]++;
    }

    int m; cin >> m;
    
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        q[x % 2]++;
    }

    //cout << '\t' << p[0] << ' ' << p[1] << ' ' << q[0] << ' ' << q[1]<< '\n';

    cout << p[0] * q[0] + p[1] * q[1] << '\n';
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
