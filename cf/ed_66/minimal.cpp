// seal orz

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

using namespace std;

int n, m;
vector<pair<int, int>> intervals;

void filter() {
    vector<pair<int, int>> res;
    sort(intervals.begin(), intervals.end(), [](auto p1, auto p2) {
        if (p1.first == p2.first) return p1 > p2;
        return p1 < p2;
    });

    int end = 0;
    for (auto [l, r] : intervals) {
        if (r > end) {
            end = r;
            res.emplace_back(l, r);
        }
    }

    intervals = res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        intervals.emplace_back(l, r);
    }

    filter();

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;

    }

    return 0;
}
