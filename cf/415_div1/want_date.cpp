// :pray: :arrayman:

#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long
#define MOD 1000000007

void mod(ll &val) {
    while (val < 0) {
        val += MOD;
    }
    
    val %= MOD;
}

using namespace std;

int main() {
    int n; cin >> n;
    vector<ll> nums;
    
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        nums.push_back(x);
    }
    
    sort(nums.begin(), nums.end());
    
    ll ans = 0;
    ll pow = 1;
    for (int i = 0; i < n; i++) {
        ans += (pow * nums[i]) % MOD;
        if (ans >= MOD) {
            ans -= MOD;
        }

        pow *= 2;
        
        if (pow > MOD) {
            pow -= MOD;
        }
    }
    
    pow = 1;
    for (int i = n - 1; i >= 0; i--) {
        ans -= (pow * nums[i]) % MOD;
        if (ans < 0) {
            ans += MOD;
        }

        pow *= 2;
        
        if (pow > MOD) {
            pow -= MOD;
        }
    }
    
    mod(ans);
    cout << ans << '\n';
}