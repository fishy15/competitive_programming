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

ll k;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> k;
    // s - n - 1 = k 
    // k + 1 + n = s
    for (int i = 1; i < 2000; i++) {
        ll s = i + k + 1;
        if (ceil(1.0 * s / i) <= 1e6) {
            vector<int> ans(i);
            for (int j = 0; j < i; j++) {
                ans[j] = s / i;
            }
            for (int j = 0; j < s - (s / i) * i; j++) {
                ans[j]++;
            }
            cout << i + 1 << '\n';
            cout << "-1 ";
            for (int j : ans) {
                cout << j << ' ';
            } cout << '\n';
            return 0;
        }
    }

    cout << "-1\n";

    return 0;
}
