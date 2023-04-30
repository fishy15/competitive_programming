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

    int n;
    cin >> n;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    for (int i = 0; i < (1 << n); i++) {
        vector<bool> vis(n);
        for (int j = 0; j < n; j++) {
            if ((i >> (n - j - 1)) & 1) {
                int r = (j - p[j] + n) % n;
                vis[r] = true;
            } else {
                int l = (j + p[j]) % n;
                vis[l] = true;
            }
        }

        if (count(vis.begin(), vis.end(), true) == n) {
            for (int j = 0; j < n; j++) {
                if ((i >> (n - j - 1)) & 1) {
                    cout << 'R';
                } else {
                    cout << 'L';
                }
            }
            cout << '\n';
            return 0;
        }
    }

    cout << "no dance\n";

    return 0;
}
