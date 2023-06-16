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

int n, q;
int nums[MAXN];
int ans[MAXN][2];
int maxi = 0;
int sz = 0;
queue<int> qq;
int head;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        maxi = max(maxi, nums[i]);
        if (i) qq.push(nums[i]);
        else head = nums[i];
    }

    while (head != maxi) {
        ans[sz][0] = head;
        ans[sz][1] = qq.front();
        sz++;

        if (head > qq.front()) {
            qq.push(qq.front());
            qq.pop();
        } else {
            int t = qq.front();
            qq.pop();
            qq.push(head);
            head = t;
        }
    }

    vector<int> rest;
    while (!qq.empty()) rest.push_back(qq.front()), qq.pop();

    while (q--) {
        ll x; cin >> x;
        if (x <= sz) {
            cout << ans[x - 1][0] << ' ' << ans[x - 1][1] << '\n';
        } else {
            x -= sz + 1;
            cout << head << ' ' << rest[x % (n - 1)] << '\n';
        }
    }

    return 0;
}
