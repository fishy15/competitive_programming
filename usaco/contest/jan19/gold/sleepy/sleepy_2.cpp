// ***************

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> bit;
int get_max_one(int n) {
    return n & (~n + 1);
}

void makeBIT(int sz) {
    bit = vector<int>(sz + 1, 0);
}

int get_before(int i) {
    if (i == 0) {
        return 0;
    }

    return bit[i] + get_before(i - get_max_one(i));
}

void add(int i) {
    while (i < bit.size()) {
        bit[i]++;
        i += get_max_one(i);
    }
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

    makeBIT(n);

    int maxPos = n - 1;
    while (maxPos > 0) {
        if (nums[maxPos] > nums[maxPos - 1]) {
            maxPos--;
        } else {
            break;
        }
    }

    for (int i = maxPos; i < n; i++) {
        add(nums[i]);
    }

    fout << maxPos << '\n';
    for (int i = 0; i < maxPos; i++) {
        int loc = get_before(nums[i]);

        fout << (maxPos - i - 1 + loc);
        if (i < maxPos - 1) {
            fout << ' ';
        } else {
            fout << '\n';
        }

        add(nums[i]);
    }

    return 0;
}