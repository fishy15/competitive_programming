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

    int n, k;
    cin >> n >> k;

    vector<ll> evals(n);
    rep(i, 0, n) {
        ll x;
        cin >> x;
        evals[i] = x;
    }

    sort(all(evals));

    ll sum_sq = 0;
    ll sum = 0;
    rep(i, 0, k) {
        sum_sq += evals[i] * evals[i];
        sum += evals[i];
    }

    ld best = sum_sq - (ld) sum / k * sum;
    rep(i, k, n) {
        sum_sq -= evals[i - k] * evals[i - k];
        sum -= evals[i - k];
        sum_sq += evals[i] * evals[i];
        sum += evals[i];
        best = min(best, sum_sq - (ld) sum / k * sum);
    }

    cout << fixed << setprecision(10);
    cout << best << '\n';

    return 0;
}
