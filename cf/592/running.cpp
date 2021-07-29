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

ll n, k;
int ans[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    k -= n * (n + 1) / 2;

    if (k < 0) {
        cout << "-1\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        ans[i] = i;
    }

    for (int i = 0; i < n; i++) {
        int o = n - i - 1;
        if (o <= i) break;
        if (k > o - i) {
            swap(ans[i], ans[o]);
            k -= o - i;
        } else {
           swap(ans[i], ans[i + k]); 
           break;
           return 0;
        }
    }

    ll sum = 0;
    for (int i = 0; i < n; i++) {
        sum += max(i + 1, ans[i] + 1);
    }

    cout << sum << '\n';
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << ' ';
    }
    cout << '\n';

    return 0;
}
