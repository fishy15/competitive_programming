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

auto count_ones(ll x) {
    int res = 0;
    while (x > 0) {
        res += x & 1;
        x /= 2;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;

    auto num_ones = count_ones(n);
    auto odds = 1LL << num_ones;
    cout << odds << '\n';

    return 0;
}
