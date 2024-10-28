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

int ask(int a, int b, int c, int d) {
    cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << endl;

    char res;
    cin >> res;

    if (res == '<') {
        return 1;
    } else if (res == '=') {
        return 0;
    } else {
        return -1;
    }
}

void ans(int i, int j) {
    cout << "! " << i << ' ' << j << endl;
}

void solve() {
    int n;
    cin >> n;

    // find maximum - n
    int best = 0;
    for (int i = 1; i < n; i++) {
        if (ask(best, best, i, i) == 1) {
            best = i;
        }
    }

    // figure out set that ORs to max - n
    vector<int> or_best = {0};
    for (int i = 1; i < n; i++) {
        auto res = ask(best, or_best[0], best, i);
        if (res == 1) {
            or_best = {i};
        } else if (res == 0) {
            or_best.push_back(i);
        }
    }

    // pick minimum out of it - n
    int min_in_set = or_best[0];
    for (int i = 1; i < (int) or_best.size(); i++) {
        if (ask(min_in_set, min_in_set, or_best[i], or_best[i]) == -1) {
            min_in_set = or_best[i];
        }
    }

    ans(min_in_set, best);
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
