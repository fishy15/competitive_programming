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

int n, k;
vector<pair<int, int>> mov;
set<int> cur;
int ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        mov.push_back({a, b});
    }

    sort(mov.begin(), mov.end(), [](const pair<int, int> &p1, const pair<int, int> &p2) {
        if (p1.second == p2.second) return p1 < p2;
        return p1.second < p2.second;
    });

    for (auto p : mov) {
        while (!cur.empty()) {
            int v = *cur.begin();
            if (v > mov.first)
        }
    }

    return 0;
}
