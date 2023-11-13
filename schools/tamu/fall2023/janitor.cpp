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
#define MAXN 100000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> x_cnt(MAXN);
    vector<int> y_cnt(MAXN);

    ll cur_x = 0;
    ll cur_y = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        x_cnt[x]++;
        y_cnt[y]++;
        cur_x += x + 1;
        cur_y += y + 1;
    }

    int bef_x = 0;
    int bef_y = 0;

    vector<ll> ans_x(MAXN);
    vector<ll> ans_y(MAXN);

    for (int i = 0; i < MAXN; i++) {
        cur_x += bef_x - (n - bef_x);
        cur_y += bef_y - (n - bef_y);
        bef_x += x_cnt[i];
        bef_y += y_cnt[i];

        ans_x[i] = cur_x;
        ans_y[i] = cur_y;
    }

    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        ll ans = 2 * (ans_x[x] + ans_y[y]);
        cout << ans << '\n';
    }
    

    return 0;
}
