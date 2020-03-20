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
ll nums[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    ll cur = 0;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < n; i++) {
        ll x = cur + nums[i];
        cout << x << ' ';
        cur = max(cur, x);
    } cout << '\n';

    return 0;
}
