#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

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

    fout << maxPos << '\n';

    return 0;
}