// idk why this doesnt work oops

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    int n, l; cin >> n >> l;
    vector<ll> nums;

    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        nums.push_back(x);
    }

    sort(nums.begin(), nums.end());

    ll max = 0;
    for (int i = 0; i < n - 1; i++) {
        ll diff = (nums[i + 1] - nums[i]);
        max = diff > max ? diff : max;
    }
 
    ll beg = 2*nums[0];
    ll end = 2*(l - nums[n - 1]);

    max = beg > max ? beg : max;
    max = end > max ? end : max;

    cout << max / 2.0 << '\n';
    return 0;
}
