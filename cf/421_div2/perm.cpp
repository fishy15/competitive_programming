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
#define MAXN 1000010

using namespace std;

int n;
int nums[MAXN];
vector<int> mod_diff[MAXN];
ll cur;
ll ans;
int id;
set<int> above;
set<int> below;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        cur += abs(nums[i] - i);
        mod_diff[(nums[i] - i + n) % n].push_back(i);
        if (nums[i] > i) above.insert(i);
        else below.insert(i);
    }

    ans = cur;

    for (int i = 1; i < n; i++) {
        int flop = n - i + 1;
        below.erase(flop);
        cur += 2 * nums[flop] - n - 1;
        int cnt = 0;
        cur += (int)(below.size());
        cur -= (int)(above.size());
        for (int j : mod_diff[i]) {
            if (j == flop) continue;
            above.erase(j);
            below.insert(j);
            cnt++;
        }
        if (nums[flop] == 1) below.insert(flop);
        else above.insert(flop);

        if (cur < ans) {
            ans = cur;
            id = i;
        }
    }

    cout << ans << ' ' << id << '\n';

    return 0;
}
