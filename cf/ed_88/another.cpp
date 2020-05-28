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
#define MAXN 100010

using namespace std;

int n;
ll nums[MAXN];
ll pre[MAXN];
ll a;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i + 1];
        pre[i + 1] = pre[i] + nums[i + 1];
    }

    for (int m = -30; m <= 30; m++) {
        ll minn = 0;
        set<int> cur;
        for (int i = 1; i <= n; i++) {
            if (nums[i] > m) {
                minn = pre[i];
                cur = {};
            } else {
                cur.insert(nums[i]);
                a = max(a, pre[i] - minn - *cur.rbegin());
                minn = min(minn, pre[i]);
            }
        }
    } 

    cout << a << '\n';

    return 0;
}
