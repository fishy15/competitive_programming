#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin("lemonade.in");
    ofstream fout("lemonade.out");

    int n; fin >> n;
    vector<int> nums;

    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        nums.push_back(x);
    }

    sort(nums.rbegin(), nums.rend());

    int c = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] >= c) {
            c++;
        }
    }

    fout << c << '\n';
}
