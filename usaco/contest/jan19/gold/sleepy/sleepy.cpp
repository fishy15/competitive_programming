// *tttttttttttttt

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> cur;

int findPos(int num) {
    int min = 0;
    int max = cur.size();
    int ans = -1;

    while (min < max) {
        int mid = (min + max) / 2;
        if (cur[mid] > num) {
            ans = mid;
            max = mid - 1;
        } else {
            ans = mid + 1;
            min = mid + 1;
        }
    }

    return ans;
}

int main() {
    ifstream fin("sleepy.in");
    ofstream fout("sleepy.out");

    int n; fin >> n;
    vector<int> nums;

    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        nums.push_back(x);
    }

    int maxPos = n - 1;
    while (maxPos > 0) {
        if (nums[maxPos] > nums[maxPos - 1]) {
            maxPos--;
        } else {
            break;
        }
    }

    //cout << maxPos << endl;
    for (int i = maxPos; i < n; i++) {
        cur.push_back(nums[i]);
    }

    fout << maxPos << '\n';
    for (int i = 0; i < maxPos; i++) {
        int loc = findPos(nums[i]);
        //cout << loc << '\n';
        fout << (maxPos - i - 1 + loc);
        if (i < maxPos - 1) {
            fout << ' ';
        } else {
            fout << '\n';
        }

        cur.push_back(nums[i]);
        sort(cur.begin(), cur.end());
    }

    return 0;
}