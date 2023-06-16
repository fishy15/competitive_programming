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

int n, k, t;
string s;
int start;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k >> t;
    cin >> s;
    for (int i = 0; i < n; i++) {
        start += (1 << i) * (s[n - i - 1] - '0');
    }

    if (k % 2 == 0 || (n > 1 && k >= n)) {
        cout << "-1\n";
        return 0;
    }

    vector<int> ans = {0, 1};
    for (int i = 1; i < n; i++) {
        int num = 1 << i;
        if (i > k) {
            num += (1 << (k - 1)) - 1;
        }
        for (int j = (1 << i) - 1; j >= 0; j--) {
            ans.push_back(ans[j] ^ num);
        }
        if (i == k) {
            for (int j = 0; j < (1 << i); j++) {
                ans[2 * j + 1] ^= (1 << (i + 1)) - 1; 
            }
        }
    }

    rotate(ans.begin(), find(ans.begin(), ans.end(), start), ans.end());

    cout << (1 << n) << '\n';
    for (int i : ans) {
        for (int j = n - 1; j >= 0; j--) {
            cout << ((i & (1 << j)) > 0);
        }
        cout << '\n';
    }

    return 0;
}
