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
#define MAXN 100

using namespace std;

int n, k;
int nums[MAXN];

void solve() {
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int pos = 1;
    int t = 0;
    
    while (t < k && pos < n) {
        if (t + pos > k) break;
        if (nums[pos] == 0) {
            pos++;
            continue;
        }
        nums[0]++;
        nums[pos]--;
        t += pos;
    }

    cout << nums[0] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
