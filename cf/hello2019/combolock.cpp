#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> nums;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    set<int> cur = {0};
    for (int i = 0; i < n; i++) {
        set<int> next;
        for (int j : cur) {
            next.insert((nums[i] + j) % 360);
            next.insert((j - nums[i] + 360) % 360);
        }

        cur = next;
    }

    if (cur.find(0) != cur.end()) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
