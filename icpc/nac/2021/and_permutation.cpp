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
#include <cassert>

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

    int n;
    cin >> n;

    vector<ll> nums(n);
    map<ll, int> rev;
    rep(i, 0, n) {
        cin >> nums[i];
        rev[nums[i]] = i;
    }

    vector<int> pair_idx(n);
    iota(all(pair_idx), 0);

    rep(p, 0, 60) {
        rep(i, 0, n) {
            if ((nums[i] >> p) & 1) {
                auto other = nums[i] ^ (1LL << p);
                swap(pair_idx[i], pair_idx[rev[other]]);
            }
        }
    }

    rep(i, 0, n) {
        cout << nums[pair_idx[i]] << '\n';
    }

    return 0;
}
