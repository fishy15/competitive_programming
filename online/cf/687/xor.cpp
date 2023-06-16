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
#define MAXN 100000

using namespace std;

int n;
int nums[MAXN];
int msb[MAXN];

int calc(int n) {
    int cur = 0;
    while ((n >> cur) != 1) cur++;
    return 1 << cur;
}

int solve(int a, int b, int c) {
    vector<int> cur;
    for (int i = 0; i < a; i++) {
        cur.push_back(nums[i]);
    }

    int tot = 0;
    for (int j = a; j <= b; j++) {
        tot ^= nums[j];
    }
    cur.push_back(tot);

    for (int i = b + 1; i < n; i++) {
        cur.push_back(nums[i]); 
    }

    int p = 0;
    for (int i : cur) {
        if (i < p) {
            return b - a;
        }
        p = i;
    }

    return INF;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        msb[i] = calc(nums[i]);
    }

    for (int i = 1; i < n - 1; i++) {
        if (msb[i - 1] == msb[i] && msb[i] == msb[i + 1]) {
            cout << "1\n";
            return 0;
        }
    }

    int ans = INF;

    for (int a = 0; a < n; a++) {
        for (int b = a; b < n; b++) {
            ans = min(ans, solve(a, b));
        }
    }

    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}
