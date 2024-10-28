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

    if (2 * count(s.begin(), s.end(), '0') != n) {
        cout << "-1\n";
        return;
    }

    int l = 0;
    int r = n - 1;
    int bef_added = 0;
    vector<int> moves;
    while (l < r) {
        if (s[l] != s[r]) {
            bef_added++;
            s = s.substr(1, n - 2);
            n -= 2;
            r -= 2;
        } else {
            if (s[l] == '1') {
                // want to shift to the beginning
                moves.push_back(bef_added);
                bef_added++;
                rotate(s.begin(), s.end() - 1, s.end());
            } else {
                // want to shift to the end
                moves.push_back(bef_added + n);
                bef_added++;
                rotate(s.begin(), s.begin() + 1, s.end());
            }
        }
    }

    cout << moves.size() << '\n';
    for (auto x : moves) {
        cout << x << ' ';
    }
    cout << endl;
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
