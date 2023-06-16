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

 
int n, k;
int kk;
int nums[MAXN];
multiset<ll> b;
multiset<ll> f;
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    sort(nums, nums + n);
 
    ll f_sum = 0;
    ll b_sum = 0;
    for (int i = 0; i < k; i++) {
        f.insert(nums[i]);
        f_sum += nums[i];
    }
    
    if (k % 2 == 0) {
        kk = k / 2 - 1;
    } else {
        kk = k / 2;
    }
 
    while (b.size() < kk) {
        int v = *f.begin();
        f.erase(f.begin());
        f_sum -= v;
        b.insert(v);
        b_sum += v;
    }
 
    ll ans;
    {
        auto median = *f.begin();
        ans = (f_sum - (ll) f.size() * median) + ((ll) b.size() * median - b_sum);
    }

    for (int i = 1; i <= n - k; i++) {
        if (b.count(nums[i - 1])) {
            b.erase(b.find(nums[i - 1]));
            b_sum -= nums[i - 1];
        } else {
            f.erase(f.find(nums[i - 1]));
            f_sum -= nums[i - 1];
        }
 
        f.insert(nums[i + k - 1]);
        f_sum += nums[i + k - 1];
 
        while (b.size() < kk) {
            int v = *f.begin();
            f.erase(f.begin());
            f_sum -= v;
            b.insert(v);
            b_sum += v;
        }
 
        while (b.size() > 0 && *b.rbegin() > *f.begin()) {
            int a = *b.rbegin();
            int c = *f.begin();
            b.erase(--b.end());
            f.erase(f.begin());
            f.insert(a);
            b.insert(c);

            b_sum -= a;
            f_sum += a;

            f_sum -= c;
            b_sum += c;
        }
 
        auto median = *f.begin();
        ans = min(ans, (f_sum - (ll) f.size() * median) + ((ll) b.size() * median - b_sum));
    }

    cout << ans << '\n';
 
    return 0;
}
