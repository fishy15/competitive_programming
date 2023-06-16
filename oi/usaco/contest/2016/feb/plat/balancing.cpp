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
#define MAXN 100000
#define MAXBIT 2 * MAXN + 5

using namespace std;

int n;
vector<pair<pair<int, int>, int>> pts;
vector<int> y;

int bit1[MAXBIT];
int bit2[MAXBIT];

void update(int x, int v, int* bit) {
    while (x < MAXBIT) {
        bit[x] += v;
        x += x & -x;
    }
}

int query(int v, int* bit) {
    int ans = 0;
    while (v) {
        ans += bit[v];
        v -= v & -v;
    }

    return ans;
}

int main() {
    ifstream fin("balancing.in");
    ofstream fout("balancing.out");

    fin >> n;
    y = {-INF};
    for (int i = 0; i < n; i++) {
        int a, b; fin >> a >> b;
        pts.push_back({{a, b}, 0});
        y.push_back(b);
    }

    sort(pts.begin(), pts.end(), [](const pair<pair<int, int>, int> &p1, const pair<pair<int, int>, int> &p2) {
        return p1.first.second < p2.first.second;
    });

    for (int i = 0; i < n; i++) {
        pts[i].second = i + 1;
        update(i + 1, 1, bit2);
    }

    sort(pts.begin(), pts.end());
    sort(y.begin(), y.end());

    int ans = INF;
    for (int i = 0; i < n; i++) {
        update(pts[i].second, 1, bit1);
        update(pts[i].second, -1, bit2);

        if (i < n && pts[i].first.first == pts[i + 1].first.first) continue;

        int l = 0;
        int r = n;
        while (l < r) {
            int mid1 = l + (r - l) / 3;
            int mid2 = r - (r - l) / 3;

            while (mid1 < n && y[mid1] == y[mid1 + 1]) mid1++;
            while (mid2 > 1 && y[mid2] == y[mid2 - 1]) mid2--;

            int lll[2];
            int rr[2];
            lll[0] = query(mid1, bit1);
            lll[1] = i + 1 - lll[0];
            rr[0] = query(mid1, bit2);
            rr[1] = n - lll[0] - lll[1] - rr[0];
            int mm1 = max(max(lll[0], lll[1]), max(rr[0], rr[1]));

            lll[0] = query(mid2, bit1);
            lll[1] = i + 1 - lll[0];
            rr[0] = query(mid2, bit2);
            rr[1] = n - lll[0] - lll[1] - rr[0];
            int mm2 = max(max(lll[0], lll[1]), max(rr[0], rr[1]));

            if (mm1 == mm2) {
                l = mid1 + 1;
                r = mid2 - 1;
            } else if (mm1 < mm2) {
                r = mid2 - 1;
            } else {
                l = mid1 + 1;
            }

            ans = min(ans, min(mm1, mm2));
        }
    }

    fout << ans << '\n';

    return 0;
}
