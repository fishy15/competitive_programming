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

int n, m;
int nums[MAXN];
int loc[MAXN];
int ans;

int calc(int x) {
    int res = 0;
    if (x != 1 && loc[x] < loc[x - 1]) res++;
    if (x != n && loc[x + 1] < loc[x]) res++;
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        loc[nums[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        if (i == 1 || loc[i - 1] > loc[i]) ans++;
    }

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        a = nums[a];
        b = nums[b];
        if (a > b) swap(a, b);
        ans -= calc(a);
        ans -= calc(b);
        if (a + 1 == b && loc[a] > loc[b]) ans++;
        swap(loc[a], loc[b]);
        swap(nums[loc[a]], nums[loc[b]]);
        ans += calc(a);
        ans += calc(b);
        if (a + 1 == b && loc[a] > loc[b]) ans--;
        cout << ans << '\n';
    }

    return 0;
}
