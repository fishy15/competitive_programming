#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n, m; cin >> n >> m;
    vector<int> nums; 
    ll sum = 0;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
        sum += x;
    }

    sort(nums.rbegin(), nums.rend());

    int counter = nums[0];
    for (int i = 1; i < n; i++) {
        counter--;
        if (counter == 0) {
            counter = 1;
        }

        if (counter > nums[i]) {
            counter = nums[i];
        } else {
            nums[i] = counter;
        }
    }

    nums.push_back(0);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int diff = nums[i] - nums[i + 1];
        ans += diff == 0 ? 1 : diff;
    }

    /*
    for (int i : nums) {
        cout << i << ' ';
    } cout << endl;
    */

    cout << sum - ans << '\n';
    return 0;
}
