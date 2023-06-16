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
#define MAXN 100000

using namespace std;

int n;
ll nums[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    ll sum = 0;
    ll mm = 0;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        sum += nums[i];
        mm = max(mm, nums[i]);
    }

    ll ans = max((sum + n - 2) / (n - 1), mm);
    cout << ans << '\n';


    return 0;
}
