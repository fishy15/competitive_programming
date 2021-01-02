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
#define MAXN 1010

using namespace std;

int n;
pair<int, int> pts[MAXN];
int ans;

ld slope(int i, int j) {
    ld dy = pts[i].second - pts[j].second;
    ld dx = pts[i].first - pts[j].first;
    return dy / dx;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> pts[i].first >> pts[i].second;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (abs(slope(i, j)) <= 1) ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}
