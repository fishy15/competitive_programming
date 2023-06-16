// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    vector<int> nums;

    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        if (x != y) {
            cout << "rated\n";
            return 0;
        }

        nums.push_back(x);
    }

    for (int i = 0; i < n - 1; i++) {
        if (nums[i] < nums[i + 1]) {
            cout << "unrated\n";
            return 0;
        }
    }

    cout << "maybe\n";

    return 0;
}
