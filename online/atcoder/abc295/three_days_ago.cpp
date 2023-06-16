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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    cin >> s;

    int psum = 0;
    array<int, 1 << 10> psum_counts{};
    psum_counts[psum]++;

    for (char c : s) {
        int x = c - '0';
        psum ^= 1 << x;
        psum_counts[psum]++;
    }

    ll ans = 0;
    for (auto x : psum_counts) {
        ans += (ll) x * (x - 1) / 2;
    }

    cout << ans << '\n';

    return 0;
}
