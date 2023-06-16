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

int n, k;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    for (int i = 0; i < (1 << n); i++) {
        vector<int> opt(n);
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                opt[j] = 1;
            } else {
                opt[j] = -1;
            }
        }

        int sum = 0;
        for (int j = 0; j < n; j++) {
            int cur = 1;
            for (int a = 0; a < k; a++) {
                cur *= opt[(j + a) % n];
            }
            sum += cur;
        }

        if (sum == 0) {
            for (int i = 0; i < n; i++) {
                cout << opt[i];
                if (i < n - 1) {
                    cout << ' ';
                } else {
                    cout << '\n';
                }
            }
            return 0;
        }
    }

    cout << "0\n";

    return 0;
}
