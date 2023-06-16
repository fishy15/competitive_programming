#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int solve(int x, int y) {
    auto [a, b] = minmax(x, y);
    if (x == 1) {
        if (y == 2) {
            return 0;
        } else {
            return 1;
        }
    } else if (x == 2) {
        if (y == 3) {
            return 1;
        } else {
            return 2;
        }
    } else {
        return 2;
    }
}

int calc(int x, int y) {
    int a = solve(x, y);
    if (a == 0) {
        return 3;
    } else if (a == 2) {
        return 2;
    } else {
        return 0;
    }
}

int main(int argc, char** argv) {
    cin.tie(0)->sync_with_stdio(0);

    srand(stoi(argv[1]));

    vector<int> nums = {1, 2, 3, 4};
    int sum = 0;
    for (int i = 0; i < 1000; i++) {
        random_shuffle(nums.begin(), nums.end());
        sum += calc(nums[2], nums[1]);
        for (int x : nums) {cout << x << ' ';}
        cout << '\n';
    }

    cout << (ld) sum / 1000 << '\n';

    return 0;
}
