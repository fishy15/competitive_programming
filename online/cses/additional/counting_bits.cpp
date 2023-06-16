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

ll n;
ll cnt;
ll ans[2]; // 0 - cnt for non-match, cnt for match

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 52; i >= 0; i--) {
        if ((1LL << i) & n) {
            ans[0] = 2 * ans[0] + cnt + ans[1];
            ans[1]++;
            cnt = 2 * cnt + 1;
        } else {
            ans[0] = 2 * ans[0] + cnt;
            cnt = 2 * cnt;
        }
    }

    cout << ans[0] + ans[1] << '\n';

    return 0;
}
