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

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> psum(n + 1);
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            psum[i + 1] = psum[i] + 1;
        } else {
            psum[i + 1] = psum[i] - 1;
        }
    }

    auto mini = *min_element(psum.begin(), psum.end());
    auto maxi = *max_element(psum.begin(), psum.end());

    if (psum.back() != 0) {
        cout << "-1\n";
    } else if (mini == 0 || maxi == 0) {
        cout << "1\n";
        for (int i = 0; i < n; i++) {
            cout << 1 << ' ';
        }
        cout << '\n';
    } else {
        cout << "2\n";
        int lst = -1;
        for (int i = 0; i < n; i++) {
            if (psum[i + 1] == 0) {
                cout << lst << ' ';
            } else {
                int cur = (psum[i + 1] > 0 ? 1 : 2);
                cout << cur << ' ';
                lst = cur;
            }
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
