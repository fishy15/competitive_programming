/*
 * If we start off with some starting mood of Q, then we can use the following greedy algorithm to pick 
 * which elements need to be removed: if the current prefix sum is less than zero, remove the most negative
 * number until it is not. Using this, we can create a list which specifies the highest mood where we have to
 * remove n elements, the highest mood where we have to remove n - 1 elements, etc. (If it is impossible or 
 * nonoptimal to have to remove a certain amounts of elements, then it is not included). This list can be
 * built using binary search. To answer the queries, binary search on this list is used.
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
#define MAXN 760
#define MAXM 200010

using namespace std;

int n, m;
ll nums[MAXN];
ll qry[MAXM];
ll maxv = 1000000000000000;

int needed(ll x) {
    priority_queue<int, vector<int>, greater<>> pq;
    int cnt = 0;
    ll cur = x;

    for (int i = 0; i < n; i++) {
        cur += nums[i];
        pq.push(nums[i]);
        while (cur < 0) {
            cur -= pq.top();
            pq.pop();
            cnt++;
        }
    }

    return cnt;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> qry[i];
    }

    int least = needed(maxv);
    int most = needed(0);
    vector<pair<ll, ll>> ans = {};

    for (int i = most; i > least; i--) {
        ll l = 0;
        ll r = maxv;
        ll a = -1;
        while (l <= r) {
            ll m = (l + r) / 2;
            int rem = needed(m);
            if (rem < i) {
                r = m - 1;
            } else if (rem == i) {
                l = m + 1;
                a = m;
            } else {
                l = m + 1;
            }
        }

        if (a != -1) {
            ans.push_back({a, i});
        }
    }

    ans.push_back({maxv, least});

    for (int i = 0; i < m; i++) {
        auto p = *lower_bound(ans.begin(), ans.end(), pair<ll, ll>{qry[i], 0});
        cout << p.second << '\n';
    }

    return 0;
}
