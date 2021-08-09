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

int h, w, n;
vector<pair<int, int>> pts;
vector<int> x;
vector<int> y;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> h >> w >> n;
    for (int i = 0; i < n; i++) {
        int px, py; cin >> px >> py;
        pts.push_back({px, py});
        x.push_back(px);
        y.push_back(py);
    }

    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    sort(y.begin(), y.end());
    y.erase(unique(y.begin(), y.end()), y.end());

    auto get = [&](vector<int> &arr, int val) { 
        return lower_bound(arr.begin(), arr.end(), val) - arr.begin(); 
    };

    for (auto [px, py] : pts) {
        cout << get(x, px) + 1 << ' ' << get(y, py) + 1 << '\n';
    }

    return 0;
}
