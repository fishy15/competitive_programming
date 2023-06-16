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
 
int n, k;
int nums[MAXN];

int sz(int l, int r) {
    if (r - l <= 0) return 1;
    return (r - l + 1) / 2 + 1;
}
 
int *solve(int l, int r) {
    if (r - l <= 0) {
        int *res = new int[1]{0};
        return res;
    } else if (r - l == 1) {
        int *res = new int[2]{0, nums[r] - nums[l]};
        return res;
    }
 
    int m = (l + r) / 2;
    int *res = new int[sz(l, r)];
    memset(res, 0x3f, sizeof(int) * sz(l, r));
 
    // use the middle section
    int *left, *right;
    left = solve(l, m - 1);
    right = solve(m + 2, r);

    int lsz = sz(l, m - 1);
    int rsz = sz(m + 2, r);
 
    int cur1 = 0;
    int cur2 = 0;
    for (int k = 0; k <= lsz + rsz - 2; k++) {
        res[k + 1] = nums[m + 1] - nums[m] + left[cur1] + right[cur2];
        if (cur1 + 1 < lsz) {
            if (cur2 + 1 < rsz) {
                if (left[cur1 + 1] - left[cur1] < right[cur2 + 1] - right[cur2]) {
                    cur1++;
                } else {
                    cur2++;
                }
            } else {
                cur1++;
            }
        } else {
            cur2++;
        }
    }
    
    delete[] left;
    delete[] right;
 
    // don't use the middle
    left = solve(l, m);
    right = solve(m + 1, r);

    lsz = sz(l, m);
    rsz = sz(m + 1, r);
 
    cur1 = 0;
    cur2 = 0;
    for (int k = 0; k <= lsz + rsz - 2; k++) {
        res[k] = min(left[cur1] + right[cur2], res[k]);
        if (cur1 + 1 < lsz) {
            if (cur2 + 1 < rsz) {
                if (left[cur1 + 1] - left[cur1] < right[cur2 + 1] - right[cur2]) {
                    cur1++;
                } else {
                    cur2++;
                }
            } else {
                cur1++;
            }
        } else {
            cur2++;
        }
    }

    delete[] left;
    delete[] right;

    return res;
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
 
    sort(nums, nums + n);
 
    int *v = solve(0, n - 1);
    cout << v[k] << '\n';
 
    return 0;
}
