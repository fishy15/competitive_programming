#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n, x; cin >> n >> x;
    vector<pair<int, int> > nums;

    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        nums.push_back(make_pair(a, 0));
        int b = a & x;
        if (a != b) {
            nums.push_back(make_pair(b, 1));
        }
    }

    /*
    for (auto p : nums) {
        cout << p.first << ' ' << p.second << '\n';
    }
    */

    sort(nums.begin(), nums.end());
    int min = 4;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i].first == nums[i - 1].first) {
            int op = nums[i].second + nums[i - 1].second;
            min = op < min ? op : min;
            //cout << nums[i].first << ' ' << nums[i - 1].first << '\n';
            //cout << nums[i].second << ' ' << nums[i - 1].second << '\n';
            //cout << "hi\n";
        }
    }

    if (min == 4) {
        cout << "-1\n";
    } else {
        cout << min << '\n';
    }

    return 0;
}
