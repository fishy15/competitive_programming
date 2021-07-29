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
#define MAXN 200000

using namespace std;

int psum[MAXN + 3];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    
    int n, k, q; cin >> n >> k >> q;

    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        psum[x]++;
        psum[y + 1]--;
    }

    for (int i = 1; i < MAXN + 3; i++) {
        psum[i] += psum[i - 1];
    }

    for (int i = 1; i < MAXN + 3; i++) {
        if (psum[i] < k) {
            psum[i] = psum[i - 1];
        } else {
            psum[i] = psum[i - 1] + 1;
        }
    }

    while (q--) {
        int l, r; cin >> l >> r;
        cout << psum[r] - psum[l - 1] << '\n';
    }

    return 0;
}
