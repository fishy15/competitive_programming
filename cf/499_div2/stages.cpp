#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    string s; cin >> s;

    if (n < k) {
        cout << "-1\n";
        return 0;
    }

    sort(s.begin(), s.end());
    vector<int> nums;

    for (int i = 0; i < n; i++) {
        nums.push_back(s[i] - 'a' + 1); 
    }

    int index = 0;
    int sum = 0;
    for (int i = 0; i < k; i++) {
        //cout << i << ' ';
        //cout << s[index] << endl;
        if (sum == 0) {
            sum += nums[index];
            continue;
        }

        int temp = index;
        while (nums[temp] == nums[index] || nums[temp] == nums[index] + 1) {
            //cout << s[index] << s[temp] << '\n';
            temp++;

            if (temp >= n) {
                cout << "-1\n";
                return 0;
            }
        }

        index = temp;
        sum += nums[index];
    }

    cout << sum << '\n';
    return 0;
}
