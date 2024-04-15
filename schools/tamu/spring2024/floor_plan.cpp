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

vector<int> divs(int x) {
    vector<int> res;
    for (int i = 1; i <= x; i++) {
        if (x % i == 0) {
            res.push_back(i);
        }
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    cin >> s;

    int n = s.size();

    vector<string> ans;
    for (auto d : divs(n)) {
        vector<string> grid(n / d);
        for (int i = 0; i < n; i++) {
            grid[i / d] += s[i];
        }

        bool valid = true;
        for (int i = 0; i < n / d; i++) {
            for (int j = 0; j < d; j++) {
                if (grid[i][j] == 'T') {
                    for (int x = -1; x <= 1; x++) {
                        for (int y = -1; y <= 1; y++) {
                            if (x == 0 && y == 0) continue;
                            int nx = x + i;
                            int ny = y + j;
                            if (nx >= 0 && ny >= 0 && nx < n / d && ny < d) {
                                if (grid[nx][ny] == 'T') {
                                    valid = false;
                                    goto out;
                                }
                            }
                        }
                    }
                }
            }
        }

out:
        if (valid) {
            ans.push_back(to_string(n / d) + "x" + to_string(d));
        }
    }

    reverse(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (auto x : ans) {
        cout << x << '\n';
    }

    return 0;
}
