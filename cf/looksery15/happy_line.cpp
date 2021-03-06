// :pray: :steph:
// :pray: :bakekaga:

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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int> nums;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    for (int i = 0; i < n; i++) {
        nums[i] -= n - i - 1;
    }

    sort(nums.begin(), nums.end());

    for (int i = 0; i < n; i++) {
        nums[i] += n - i - 1;
    }

    int prev = -1;
    for (int i : nums) {
        if (i < 0 || i < prev) {
            cout << ":(\n";
            return 0;
        }
        prev = i;
    }

    for (int i : nums) {
        cout << i << ' ';
    } cout << '\n';

    return 0;
}
