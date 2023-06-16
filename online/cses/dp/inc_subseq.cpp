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
#define MAXN 200000

using namespace std;

int n;
vector<int> nums;
int ans;
map<int, int> back;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    nums.resize(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    for (int i : nums) {
        auto it = back.lower_bound(i);
        if (it == back.begin()) {
            back[i] = 1;
        } else {
            it--;
            back[i] = max(back[i], it->second + 1);
        }

        it = back.find(i);
        while (it != back.end()) {
            auto it2 = it;
            it2++;
            if (it2 == back.end()) break;
            if (it2->second <= it->second) {
                back.erase(it2);
            } else {
                break;
            }
        }

        ans = max(it->second, ans);
    }

    cout << ans << '\n';
    return 0;
}
