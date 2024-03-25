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

    int n, a, b;
    cin >> n >> a >> b;

    bool reach_min = false;
    bool reach_max = false;
    for (int i = 0; i < n - 1; i++) {
        int x;
        cin >> x;

        if (x < a || x > b) {
            cout << "-1\n";
            return 0;
        }

        if (x == a) reach_min = true;
        if (x == b) reach_max = true;
    }

    if (!reach_min && !reach_max) {
        cout << "-1\n";
    } else if (!reach_min) {
        cout << a << '\n';
    } else if (!reach_max) {
        cout << b << '\n';
    } else {
        for (int i = a; i <= b; i++) {
            cout << i << '\n';
        }
    }

    return 0;
}
