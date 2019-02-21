#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int index1;
vector<int> nums;

bool works(int days);

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    cin >> n >> m;

    vector<int> pack;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        pack.push_back(x);
    }

    sort(pack.begin(), pack.end());
    index1 = -1;
    for (int i = 0; i < m; i++) {
        if (i > 0 && pack[i] == pack[i - 1]) {
            nums[index1]++;
        } else {
            index1++;
            nums.push_back(1);
        }
    }

    /*
    for (int i : nums) {
        cout << i << ' ';
    }

    cout << endl;
    int min = 0;
    int max = 100;
    */
    /*
    while (min < max) {
        int mid = (min + max) / 2;
        if (works(mid)) {
            min = mid + 1;
        } else {
            max = mid - 1;
        }

        cout << "MM: " <<  min << ' ' << max << endl;;
    }
    */

    int x;
    for (x = 1; x <= 100; x++) {
        if (!works(x)) {
            break;
        }
    }

    cout << x - 1 << '\n';
    return 0;
}

bool works(int days) {
    if (days == 0) {
        return true;
    }

    int total = 0;
    for (int i : nums) {
        total += i / days;
    }

    //cout << "days: " << days << ' ' << total << endl;
    return total >= n;
}
