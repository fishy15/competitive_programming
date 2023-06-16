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

int n;

int sum(const vector<int> &v) {
    int s = 0;
    for (int x : v) s += x;
    return s;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    if (n % 3 == 0) {
        vector<vector<int>> v = {{1}, {2}, {3}};
        for (int i = 0; i < (n - 3) / 3; i++) {
            v[2].push_back(3 * i + 4);
            v[0].push_back(3 * i + 5);
            v[1].push_back(3 * i + 6);
            v[1].swap(v[2]);
        }
        vector<int> ans(n + 1);
        for (int x : v[0]) ans[x] = 1;
        for (int x : v[1]) ans[x] = 2;
        for (int x : v[2]) ans[x] = 3;
        for (int i = 1; i <= n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    } else if (n % 3 == 1) {
        cout << "IMPOSSIBLE\n";
    } else {
        vector<vector<int>> v = {{1, 3}, {5}, {2, 4}};
        for (int i = 0; i < (n - 5) / 3; i++) {
            v[2].push_back(3 * i + 6);
            v[0].push_back(3 * i + 7);
            v[1].push_back(3 * i + 8);
            v[1].swap(v[2]);
        }
        vector<int> ans(n + 1);
        for (int x : v[0]) ans[x] = 1;
        for (int x : v[1]) ans[x] = 2;
        for (int x : v[2]) ans[x] = 3;
        for (int i = 1; i <= n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
