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
#define MAXN 1000000

using namespace std;

int n;
int s[MAXN];
vector<int> adj[MAXN];

ll solve(int x) {
    ll ans = s[x];
    for (int e : adj[x]) {
        ans += s[e];
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, solve(i));
    }

    cout << ans << '\n';

    return 0;
}
