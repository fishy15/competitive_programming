#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> nums;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    vector<int> diff;
    diff.push_back(nums[0]);

    for (int i = 1; i < n; i++) {
        int x = nums[i] - nums[i - 1];
        diff.push_back(x);
    }

    vector<int> ans;

    // size of k
    for (int i = 1; i <= n; i++) {
        bool bad = false;
        // loop over 0..k-1
        for (int j = 0; j < i; j++) {
            int val = j;
            while (val < n) {
                if (diff[val] != diff[j]) {
                    bad = true;
                    break;
                }

                val += i;
            }
        }

        if (!bad) {
            ans.push_back(i);
        }
    }

    cout << ans.size() << '\n';
    for (int i : ans) {
        cout << i << ' ';
    }

    cout << '\n';
    return 0;
}
