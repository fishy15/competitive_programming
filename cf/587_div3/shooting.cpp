// :pray: :fishy:

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

    int n;
    vector<pair<int, int>> nums;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back({x, i});
    }

    sort(nums.begin(), nums.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
            return a.first > b.first;
    });

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += i * nums[i].first + 1;
    }

    cout << ans << '\n';
    for (int i = 0; i < n; i++) {
        cout << nums[i].second + 1 << ' ';
    }

    return 0;
}
