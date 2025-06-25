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
#include <optional>

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

array<optional<int>, 30> basis;

void add(int x) {
    rep(i, 0, 30) {
        if ((x >> i) & 1) {
            if (basis[i]) {
                x ^= *basis[i];
            } else {
                basis[i] = x;
                return;
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    int psum = 0;
    rep(i, 0, n) {
        int x;
        cin >> x;
        psum ^= x;
        add(x);
    }

    int basis_sz = 0;
    rep(i, 0, 30) {
        if (basis[i]) {
            basis_sz++;
        }
    }

    if (psum == 0) {
        cout << "-1\n";
    } else {
        cout << basis_sz << '\n';
    }

    return 0;
}
