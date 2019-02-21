#include <iostream>
#include <vector>

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n, b; cin >> n >> b;
    vector<bool> nums(b, false);
    nums[0] = true;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        x %= b;
        bool exit = true;
        while (true) {
            for (int i = 0; i < b; i++) {
                if (nums[i]) {
                    int val = (i + x) % b;
                    //cout << val << '\n';
                    if (!nums[val]) {
                        nums[val] = true;
                        exit = false;
                    }
                }
            }

            if (exit) {
                break;
            }

            exit = true;
        }
    }

    int ans = 0;
    vector<int> ansNum;
    for (int i = 0; i < b; i++) {
        //cout << i << ' ';
        if (nums[i]) {
            ansNum.push_back(i);
            ans++;
        }
    }

    cout << ans << '\n';
    for (int i : ansNum) {
        cout << i << ' ';
    }

    cout << '\n';
}
