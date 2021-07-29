/**
 * Each node contributes D + 1 to the sum, where D is its depth from the root. This means that for a given
 * value of k as the upper limit of the number of children of a node, the max value is if the tree was a 
 * line graph and the min value is if is structured like a k-nary tree with all the upper levels full with 
 * children. Let s(k) be the minimum value we can get from a value of k. We can find the smallest value of  
 * k such that s(k) is less or equal to the given sum s, and then use that value of k to construct the
 * k-nary tree. To increase the sum, we can add merge two adjacent line graphs, usually by placing one of 
 * the graphs below the other. If this merging would go over the correct answer, then we can merge 1 by 1
 * until we get the right sum. This merging only makes lines with at max 1 extra child, so this merging
 * does not increase the degree.
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
#define MAXN 100010

using namespace std;

ll n, s;
vector<int> child[MAXN];
int par[MAXN];
ll sz[MAXN];
int bot[MAXN];
ll diff;

ll check(int x) {
    ll res = 1;
    queue<pair<int, int>> q;
    q.push({1, 0}); // depth, degree
    for (int i = 2; i <= n; i++) {
        q.front().second++;
        res += q.front().first + 1;
        q.push({q.front().first + 1, 0});
        if (q.front().second == x) {
            q.pop();
        }
    }
    return res;
}

ll sum(ll n) {
    return n * (n + 1) / 2;
}

int merge(int a, int b) {
    /* cout << "merge " << a << ' ' << b << '\n'; */
    if (sz[a] < sz[b]) swap(a, b); 
    if (diff + sum(sz[a]) + sum(sz[b]) - sum(sz[a] + sz[b]) >= 0) {
        /* cout << "done " << a << ' ' << b << '\n'; */
        /* cout << "change " << sum(sz[a]) + sum(sz[b]) - sum(sz[a] + sz[b]) << '\n'; */
        par[b] = bot[a];
        bot[a] = bot[b];
        diff += sum(sz[a]) + sum(sz[b]) - sum(sz[a] + sz[b]);
        sz[a] += sz[b];
    } else {
        while (diff + sz[b] - sz[a] - 1 >= 0) {
            /* cout << "move " << a << ' ' << b << '\n'; */
            int tmp = par[bot[b]];
            par[bot[b]] = bot[a];
            bot[a] = bot[b];
            bot[b] = tmp;
            diff += sz[b] - sz[a] - 1;
            /* cout << "change " << sz[b] - sz[a] - 1 << '\n'; */
            sz[b]--;
            sz[a]++;
        }

        int cur = bot[a];
        int cur_sz = sz[a];
        while (diff + sz[b] - cur_sz - 1 != 0) {
            cur = par[cur];
            cur_sz--;
        }
        /* cout << "place " << a << ' ' << b << ' ' << cur_sz << ' ' << cur << '\n'; */
        /* cout << "now at 0\n"; */
        par[bot[b]] = cur;
        diff = 0;
    }
    return a;
}

void dfs(int v) {
    sz[v] = 1;
    bot[v] = v;
    for (int e : child[v]) {
        dfs(e);
        sz[v] += sz[e];
    }
    if (!child[v].empty()) {
        int cur = child[v][0];
        for (auto it = next(child[v].begin()); it != child[v].end() && diff; it++) {
            cur = merge(cur, *it);
        }
        bot[v] = bot[cur];
    }
    /* cout << v << ' ' << bot[v] << '\n'; */
}

void build(int x) {
    ll res = 1;
    queue<array<int, 3>> q;
    q.push({1, 0, 1});
    for (int i = 2; i <= n; i++) {
        auto &top = q.front();
        top[1]++;
        res += top[0] + 1;
        q.push({top[0] + 1, 0, i});
        child[top[2]].push_back(i);
        par[i] = top[2];
        if (top[1] == x) {
            q.pop();
        }
    }

    diff = s - res;
    dfs(1);

    for (int i = 2; i <= n; i++) {
        cout << par[i] << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> n >> s;

    if (n * (n + 1) / 2 < s) {
        cout << "No\n";
        return 0;
    }

    int l = 1;
    int r = n - 1;
    int ans = -1;

    while (l <= r) {
        int m = (l + r) / 2;
        ll x = check(m);
        if (x <= s) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    if (ans != -1) {
        cout << "Yes\n";
        build(ans);
    } else {
       cout << "No\n";
    }

    return 0;
}
