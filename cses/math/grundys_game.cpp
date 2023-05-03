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

// no known 0 state exists above this
constexpr int MAX_CALC = 1300;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<int> nimber(MAX_CALC);
    for (int i = 0; i < MAX_CALC; i++) {
        set<int> ok;

        for (int j = 1; 2 * j < i; j++) {
            ok.insert(nimber[j] ^ nimber[i - j]);
        }

        int cur = 0;
        while (ok.count(cur)) {
            cur++;
        }

        nimber[i] = cur;
    }

    int t;
    cin >> t;
    while (t--) {
        int x;
        cin >> x;

        if (x < MAX_CALC && nimber[x] == 0) {
            cout << "second\n";
        } else {
            cout << "first\n";
        }
    }

    return 0;
}
