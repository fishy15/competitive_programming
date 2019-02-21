// this doesnt work (mle)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<int> make_diff(vector<int> v);
vector<int> fix(vector<int> v);

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    ll w, h; cin >> w >> h;
    ll sum = 0;
    ll max = 0;
    vector<int> nums;
    nums.push_back(0);
    for (ll i = 0; i < w; i++) {
        ll x; cin >> x;
        sum += x;
        max = x > max ? x : max;
        nums.push_back(x);
    }

    sort(nums.begin(), nums.end());
    ll remain = 0;
    nums = make_diff(nums);
    nums = fix(nums);

    for (ll i = 1; i < nums.size(); i++) {
        ll diff = nums[i] - nums[i - 1];
        remain += diff == 0 ? 1 : diff;
    }

    /*
    for (auto x : nums) {
        cout << x << ' ';
    } cout << endl;
    if (max == w) {
        remain = max;
    } else if (max < w) {
        remain = w;
    } else if (max > w) {
        remain = max;
    }
    */

    cout << sum - remain << endl;
    return 0;
}

vector<int> make_diff(vector<int> v) {
    for (ll i = 0; i < v.size() - 1; i++) {
        if (v[i] == v[i + 1]) {
            v[i]--;
            return make_diff(v);
        }
    }

    return v;
}

vector<int> fix(vector<int> v) {
    v[0] = 0;
    for (ll i = 1; i < v.size(); i++) {
        if (v[i] <= 0) {
            v[i] = 1;
        } else {
            break;
        }
    }

    return v;
}
