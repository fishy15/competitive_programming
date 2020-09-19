#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin("baseball.in");
    ofstream fout("baseball.out");

    int N; fin >> N;
    vector<int> nums;

    for (int i = 0; i < N; i++) {
        int x; fin >> x;
        nums.push_back(x);
    }

    sort(nums.begin(), nums.end());
