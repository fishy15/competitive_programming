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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, m;
int k;
vector<int> a;
vector<int> b;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a.push_back(x);
    }

    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        b.push_back(x);
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int cur = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        while (cur < m && a[i] - k > b[cur]) cur++;
        if (cur < m && a[i] + k >= b[cur]) {
            ans++;
            cur++;
        }
    }

    cout << ans << '\n';

    return 0;
}
