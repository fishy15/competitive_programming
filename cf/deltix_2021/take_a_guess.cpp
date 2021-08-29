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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, k;
ll nums[MAXN];

int ask_or(int a, int b) {
    cout << "or " << a << ' ' << b << endl;
    int res; cin >> res;
    if (res == -1) exit(0);
    return res;
}

int ask_and(int a, int b) {
    cout << "and " << a << ' ' << b << endl;
    int res; cin >> res;
    if (res == -1) exit(0);
    return res;
}

void finish(int ans) {
    cout << "finish " << ans << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        nums[i] = ask_or(1, i + 1) + ask_and(1, i + 1);;
    }

    ll two_three = ask_or(2, 3) + ask_and(2, 3);
    nums[0] = (nums[1] + nums[2] - two_three) / 2;

    for (int i = 1; i < n; i++) {
        nums[i] -= nums[0];
    }

    sort(nums, nums + n);

    finish(nums[k - 1]);

    return 0;
}
