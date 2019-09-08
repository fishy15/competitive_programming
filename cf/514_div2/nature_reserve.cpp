// :pray: :fishy:

#include <iostream>
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

int n;
vector<pair<double, double>> pts;

double calc(double x) {
    double max_r = 0;
    for (int i = 0; i < n; i++) {
        double r = (x - pts[i].first) * (x - pts[i].first) + pts[i].second * pts[i].second;
        r /= 2;
        r /= pts[i].second;
        max_r = max(r, max_r);
    }

    return max_r;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    bool pos = false;
    bool neg = false;

    for (int i = 0; i < n; i++) {
        double x, y; cin >> x >> y;
        if (y > 0) {
            pos = true;
            pts.push_back({x, y});
        } else {
            neg = true;
            pts.push_back({x, -y});
        }
    }

    if (pos && neg) {
        cout << "-1\n";
        return 0;
    }

    double l = -1e7;
    double r = 1e7;
    double ans = INFLL;

    while (r - l > eps) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double r1 = calc(m1);
        double r2 = calc(m2);

        if (r1 - r2 > eps) {
            l = m1;
        } else if (r2 - r1 > eps) {
            r = m2; 
        } else {
            l = m1;
            r = m2;
        }

        ans = min(ans, r1);
        ans = min(ans, r2);
    }

    cout << fixed << ans << '\n';

    return 0;
}
