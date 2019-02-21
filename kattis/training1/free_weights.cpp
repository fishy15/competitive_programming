#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void makeSmall();
int binSearch(int, int);
bool check(int);

vector<int> top;
vector<int> bottom;
vector<int> nums;

int main() {
    int n; cin >> n;
    top = vector<int>(n);
    bottom = vector<int>(n);

    for (int i = 0; i < n; i++) {
        cin >> top[i];
        nums.push_back(top[i]);
    }

    for (int i = 0; i < n; i++) {
        cin >> bottom[i];
        nums.push_back(bottom[i]);
    }

    sort(nums.begin(), nums.end());
    makeSmall();

    cout << binSearch(0, n) << '\n';
}

void makeSmall() {
    vector<int> ans;
    ans.push_back(0);
    for (int i = 0; i < nums.size(); i += 2) {
        ans.push_back(nums[i]);
    }

    nums = ans;
}

int binSearch(int low, int high) {
    int ans = -1;
    while (low <= high) {
        //cout << low << ' ' << high << '\n';
        int mid = (low + high) / 2;
        if (check(nums[mid])) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return nums[ans];
}

bool check(int n) {
    int prev = 0;
    for (int i = 0; i < top.size(); i++) {
        if (top[i] > n) {
            if (prev == 0) {
                prev = top[i];
            } else {
                if (prev != top[i]) {
                    return false;
                }

                prev = 0;
            }
        }
    }

    if (prev != 0) {
        return false;
    }

    for (int i = 0; i < bottom.size(); i++) {
        if (bottom[i] > n) {
            if (prev == 0) {
                prev = bottom[i];
            } else {
                if (prev != bottom[i]) {
                    return false;
                }

                prev = 0;
            }
        }
    }

    if (prev != 0) {
        return false;
    }
    
    return true;
}
