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
#define MAXN 100010

using namespace std;

int m, n;
int nums[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> m >> n;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    ll cur = 0;
    for (int i = 0; i < n; i++) {
        cur += nums[i];
        if (cur > m) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << n << '\n';

    return 0;
}
