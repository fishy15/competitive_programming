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
#define MAXN 5000

using namespace std;

int n;
ll x;
ll nums[MAXN];
map<ll, int> pos;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (pos.count(x - nums[i] - nums[j])) {
                cout << i + 1 << ' ' << j + 1 << ' ' << pos[x - nums[i] - nums[j]] + 1 << '\n';
                return 0;
            }
        }
        pos[nums[i]] = i;
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
