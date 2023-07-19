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
#define MAXN 200000

using namespace std;

int v[MAXN + 1];
int v_f[MAXN + 1];

void precalc() {
    for (int i = 2; i <= MAXN; i++) {
        if (i % 2 == 0) {
            v[i] = v[i / 2] + 1;
        }

        v_f[i] = v_f[i - 1] + v[i];
    }
}

int v_c(int n, int k) {
    return v_f[n] - v_f[k] - v_f[n - k];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int n;
    cin >> n;
    
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int c = v_c(n - 1, i);
        if (c == 0) {
            ans ^= nums[i];
        }
    }

    cout << ans << '\n';

    return 0;
}
