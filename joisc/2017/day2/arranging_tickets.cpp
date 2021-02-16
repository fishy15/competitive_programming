/*
 * We can first split the circle at 0, initially marking each range from the lower number to the higher 
 * number. First, we note that we never want to flip both [a, b) and [c, d) where a < b <= c < d. This
 * increases the count at each location not within the ranges by 2, and the values within the ranges don't
 * change. Therefore, this only makes the situation worse.
 *
 * We can then binary search for the answer. Let the answer we are checking for be m. We can also define 
 * two other parameters: n will be the total number of ranges flipped, and t will be a point that all the
 * ranges flipped will have in common (which must exist as we have shown earlier). For a given point, if 
 * there are currently a people that go over the point and there are n' tickets left to assign, then the
 * amount of ranges we have to flip is max(ceil((a + n' - m) / 2), 0). We maintain a set of ranges to flip
 * and then greedily flip the rightmost edges in the set, flipping as many as we need. Afterwards, we can 
 * do a final check to see if it works. Overall, this is O(n^2 m log(n) log(sum of c)).
 *
 * We can do two optimizations to this. First, we will try to limit the values of n that we will check.
 * Let a_i denote the initial values, and b_i be the values after doing all necessary flips. We will prove
 * that we can always pick a value of t such that b_t =  or b_t = max(b_i) - 1. First of all, t can
 * be any value in the intersection of all the ranges picked, so we can choose t to have the maximum value 
 * in the range. Now, suppose that there is some value outside of the intersection i such that b_i > b_t. 
 * We can then unflip both the flipped intervals with the leftmost right bound and the rightmost left bound
 * If both ranges are distinct, then the b_i value of everything within the intersection will increase by
 * +2 (increase by +1 if the ranges are not distinct). By repeating this process, we will either end up
 * with b_t = m or b_t = m - 1, so our proof is done. Since n ranges will cover t, the b_t = a_t - n, 
 * so n = a_t - m or n = a_t - m + 1.
 *
 * Now, we want to limit the values of t that we have to check. We can first limit the candidates to t to 
 * be the values of i where a_i is the maximum of the array. If we let x_i denote the number of ranges
 * flipped that include location i, then we know that x_j < x_t if j is not in the intersection. Taking the
 * maximum possible value of b_j, we have b_j <= b_t + 1 and x_j + 1 <= x_t. Since a_i = x_i + b_i, we get
 * that a_j <= a_t if j is not in the interesction, so a_t must be the maxmimum of a. 
 *
 * Next, we will show that we only need to check the leftmost and rightmost indices where a_i is at its 
 * maximum. Denote these left and right indices by l and r. First, we will show that there is no need to
 * flip a range [c, d) where l < c < d <= r. Suppose that there is some such range that we flip. If we 
 * unflip it, then everything outside the range decrements by 1, so it is still valid. Everything inside
 * of the range increments by 1 as well. However, since x_l > x_t since l is not within the intersection
 * of all flipped intervals, b_l > b_t originally, so incrementing b_t by 1 does not make the configuration 
 * invalid. Therefore, every interval that we flip must either include l or r. If there exists two intervals
 * where one does not include l and the other does not include r, then we can unflip both of them. Let b' 
 * represent the new values at each location. For similar reasons as before, b'_l >= b'_i for l <= i <= r
 * because a_l and a_r are the max values of a over the entire array, but x'_l and x'_r are still the 
 * lowest values between l and r (since they are the farthest from t). Everything outside of l and r will 
 * either not change in value or decrease by 2, so overall, the combination is still valid. We can keep 
 * repeating this process until all remaining ranges contain either l or r, so we could have chosen t = l
 * or t = r. Therefore, we only need to check these two location.
 *
 * Overall, this cuts a factor of O(nm) from the solution, so the new time complexity is 
 * O(n log(n) log(sum of c)), which passes.
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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n, m;
vector<array<int, 3>> range[MAXN];
ll init[MAXN];
int min_check, max_check;

struct cmp {
    bool operator()(const array<int, 3> &a, const array<int, 3> &b) const {
        if (a[1] == b[1]) {
            if (a[0] == b[0]) {
                return a[2] < b[2];
            }
            return a[0] > b[0];
        }
        return a[1] < b[1];
    }
};

struct bit {
    ll vals[MAXN];
    void reset() {
        for (int i = 0; i < n + 10; i++) {
            vals[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            ll x = init[i];
            if (i) x -= init[i - 1];
            upd(i, x);
        }
    }
    void upd(int x, ll v) {
        x++;
        while (x < n + 10) {
            vals[x] += v;
            x += x & -x;
        }
    }
    void upd(int l, int r, ll v) {
        upd(l, v);
        upd(r, -v);
    }
    ll qry(int x) {
        x++;
        ll res = 0;
        while (x) {
            res += vals[x];
            x -= x & -x;
        }
        return res;
    }
} b;

ll check(ll m, ll n, ll t) {
    b.reset();
    priority_queue<array<int, 3>, vector<array<int, 3>>, cmp> pq;
    for (int i = 0; i <= t; i++) {
        ll need_rem = max((b.qry(i) + n - m + 1) / 2, 0LL);
        n -= need_rem;
        for (auto &arr : range[i]) {
            if (arr[1] > t) {
                pq.push(arr);
            }
        }
        while (need_rem) {
            if (pq.empty()) {
                return false;
            }
            auto t = pq.top(); pq.pop();
            ll to_rem = min<ll>(t[2], need_rem);
            b.upd(0, t[0], to_rem);
            b.upd(t[0], t[1], -to_rem);
            b.upd(t[1], ::n, to_rem);
            t[2] -= to_rem;
            need_rem -= to_rem;
            if (t[2]) pq.push(t);
        }
    }

    for (int i = 0; i < ::n; i++) {
        if (b.qry(i) > m) {
            return false;
        }
    }

    return true;
}

ll check(ll m) {
    ll a = init[min_check];
    return check(m, a - m, min_check) || check(m, a - m + 1, min_check)
        || check(m, a - m, max_check) || check(m, a - m + 1, max_check);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        if (a > b) swap(a, b);
        init[a] += c;
        init[b] -= c;
        range[a].push_back({a, b, c});
    }

    for (int i = 1; i < n; i++) {
        init[i] += init[i - 1];
    }

    for (int i = 0; i < n; i++) {
        if (init[i] > init[min_check]) {
            min_check = i;
            max_check = i;
        } else if (init[i] == init[min_check]) {
            max_check = i;
        }
    }

    ll l = 0;
    ll r = init[min_check];
    ll ans = init[min_check];

    while (l <= r) {
        ll m = (l + r) / 2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}
