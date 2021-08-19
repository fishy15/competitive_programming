/*
 * For the n = 1 case, the solution is just the length of the interval. For n = 2, any pair of integers is
 * a valid sequence, so the answer is the number of ordered pairs. 
 *
 * For higher numbers, we can compute the answer is an algorithm that is up to approximately O(sz^2 log sz),
 * where sz is the length of the interval. Specifically, we note that if each term is an integer, 
 * then the first number is a multiple of denominator^n. Therefore, the first multiple of denom^n >= l is
 * the first potential value. In addition, we need to check that multiplying by numerator^n is within the
 * range from l to r, and we can count how many numbers are in this range by dividing. We can iterate 
 * over all values of denom (until denom^n >= r, so the smallest number is outside of the range), and then
 * iterate over all values of numer (until (numerator / denominator) ^ n * l is >= r) and add the answer
 * for all pairs where gcd(numer, gcd) = 1.
 */
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

int n, l, r;

ll mul(ll a, ll b) {
    return min<ll>(a * b, INF);
}

ll limpow(ll n, ll e) {
    ll res = 1;
    while (e > 0) {
        if (e & 1) res = mul(res, n);
        n = mul(n, n);
        e >>= 1;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> l >> r;
    if (n == 1) {
        cout << (r - l + 1) << '\n';
    } else if (n == 2) {
        cout << (ll) (r - l + 1) * (r - l) << '\n';
    } else {
        ll denom = 1;
        ll pd;
        ll ans = 0;
        while (pd = limpow(denom, n - 1), pd <= r) {
            ll after_div = (l + pd - 1) / pd;

            ll num = 1;
            ll pn;
            while (pn = limpow(num, n - 1), after_div * pn <= r) {
                if (num != denom && gcd(num, denom) == 1) {
                    ll left_bound = max<ll>(after_div, (l + pn - 1) / pn);
                    ll right_bound = min(r / pd, r / pn);
                    ans += max(0LL, right_bound - left_bound + 1);
                }
                num++;
            }
            denom++;
        }

        cout << ans << '\n';
    }

    return 0;
}
