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

int n, l;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> l;

    vector<int> ss(l);
    ss[l - 1] = 2;
    for (int i = 0; i < n; i++) {
        int cur = i;
        for (int j = 0; j < l - 1; j++) {
            ss[j] = cur % 3;
            cur /= 3;
        }

        for (int j = 0; j < 3; j++) {
            for (int k = l - 1; k >= 0; k--) {
                cout << (j + ss[k]) % 3;
            }
            cout << '\n';
        }
    }

    return 0;
}
