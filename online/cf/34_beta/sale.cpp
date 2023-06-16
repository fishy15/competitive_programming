#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<int> nums;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    sort(nums.begin(), nums.end());
    int sum = 0;

    for (int i = 0; i < k; i++) {
        if (nums[i] >= 0) {
            break;
        }

        sum += -nums[i];
    }

    cout << sum << '\n';
    return 0;
}
