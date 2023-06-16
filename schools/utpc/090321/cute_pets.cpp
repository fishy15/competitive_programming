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

int n;
array<int, 2> a[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
    }

    sort(a, a + n);

    for (int i = 0; i < n - 1; i++) {
        if (a[i][1] > a[i + 1][1]) {
            cout << "yes\n";
            return 0;
        }
    }

    cout << "no\n";

    return 0;
}
