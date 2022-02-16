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
#define MAXN 10010

using namespace std;

int n;
bool vis[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    int cur = 0;
    for (int i = 0; i < 100 * n; i++) {
        vis[cur] = true;
        cur = (cur + i) % n;
    }

    if (all_of(vis, vis + n, [&](bool x) { return x; })) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
