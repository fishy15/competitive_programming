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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    array<int, 8> nums;
    for (int &x : nums) cin >> x;

    for (int i = 0; i < 7; i++) {
        if (nums[i] > nums[i + 1]) {
            cout << "No\n";
            return 0;
        }
    }

    for (int i = 0; i < 8; i++) {
        if (nums[i] < 100 || nums[i] > 675) {
            cout << "No\n";
            return 0;
        } else if (nums[i] % 25 != 0) {
            cout << "No\n";
            return 0;
        }
    }

    cout << "Yes\n";

    return 0;
}
