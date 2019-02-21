#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<int> nums;

    // won't work if n = k because nothing will be added to array
    if (n <= k) {
        cout << "1\n1\n";
        return 0;
    }

    int start = 0;
    while (true) {
        int loc = start;
        while (loc + k < n) {
            //cout << loc << '\n';
            loc += k + 1;
            nums.push_back(loc);
            //cout << "added: " << loc << '\n';
            loc += k;
            //cout << "Hi: " << loc << '\n';
        }

        if (nums[nums.size() - 1] + k < n) {
            start--;
            nums = vector<int>();
            continue;
        }

        cout << nums.size() << '\n';
        for (int i = 0; i < nums.size(); i++) {
            cout << nums[i] << ' ';
        }

        cout << '\n';
        return 0;
    }

    return 0;
}
