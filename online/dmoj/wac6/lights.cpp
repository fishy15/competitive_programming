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
#define MAXN 200010

using namespace std;

int n, m;
int a[MAXN];
int change[MAXN];
int to_fix;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i]) to_fix++;
    }

    for (int i = 0; i < m; i++) {
        cin >> change[i];
        change[i]--;
    }

    if (!to_fix) {
        cout << "0\n";
        return 0;
    }

    for (int i = 0; i < m; i++) {
        int &cur = a[change[i]];
        cur = !cur;
        if (cur) to_fix++;
        else to_fix--;
        if ((i + 1) >= to_fix) {
            cout << i + 1 << '\n';
            return 0;
        }
    }

    cout << to_fix << '\n';

    return 0;
}
