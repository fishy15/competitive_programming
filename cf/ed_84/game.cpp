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
#define MAXN 200

using namespace std;

int n, m, k;
pair<int, int> s[MAXN];
pair<int, int> e[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        cin >> s[i].first >> s[i].second;
    }

    for (int i = 0; i < k; i++) {
        cin >> e[i].first >> e[i].second; 
    }

    string ans = "";

    for (int i = 0; i < n - 1; i++) {
        ans += "U";
    }

    for (int i = 0; i < m - 1; i++) {
        ans += "L";
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n - 1; j++) {
            ans += i % 2 == 0 ? "D" : "U";
        }
        if (i < m - 1) ans += "R";
    }

    cout << ans.size() << '\n';
    cout << ans << '\n';

    return 0;
}
