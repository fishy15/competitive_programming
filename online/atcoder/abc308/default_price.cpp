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
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<string> has(n);
    for (auto &s : has) {
        cin >> s;
    }

    vector<string> color(m);
    for (auto &s : color) {
        cin >> s;
    }

    int def;
    cin >> def;

    map<string, int> price;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        price[color[i]] = x;
    }

    int ans = 0;
    for (const auto &s : has) {
        if (price.count(s)) {
            ans += price[s];
        } else {
            ans += def;
        }
    }

    cout << ans << '\n';


    return 0;
}
