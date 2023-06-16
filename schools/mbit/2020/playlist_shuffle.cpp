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

int n, b, x, y;
double pp;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> b >> x >> y;

    int cur = 0;
    double ewalk = 0;
    double qq = INFLL;
    for (int d = 0; d < n; d++) {
        int cnt = 0;
        if (b - d >= 1) {
            cnt++;
        } 
        if (b + d <= n && d != 0) {
            cnt++;
        }
        cur += cnt;

        double p = (double) cur / n;
        double ans = 0;
        ans += y * (1 - p) / p; 

        if (d == 1) {
            ewalk = (double) cnt / cur;
        } else {
            ewalk *= (double) (cur - cnt) / cur;
            ewalk += (double) cnt / cur * d;
        }

        ans += ewalk * x;
        qq = min(qq, ans);
        if (fabs(pp - qq) < eps) break;
        pp = qq;
    }

    cout << fixed << setprecision(12) << qq << '\n';

    return 0;
}
