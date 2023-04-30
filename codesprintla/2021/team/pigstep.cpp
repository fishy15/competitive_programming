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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int l = 1;
    int r = 500;
    bool sw = false;

    while (l < r) {
        int m = (l + r) / 2;
        cout << "ASK " << 1 << ' ' << m << endl;
        string res1, res2; cin >> res1 >> res2;

        if (res1 == res2) {
            if (res1 == "yes") {
                r = m;
            } else {
                l = m + 1;
            }
        } else {
            if (res1 == "no") {
                sw = true;
            }
            break;
        }
    }

    if (l == r) {
        cout << "GUESS " << l << ' ' << l << ' ' << endl;
        return 0;
    }

    // split into two halfs
    pair<int, int> lower = {l, (l + r) / 2};
    pair<int, int> higher = {(l + r) / 2 + 1, r};

    while (lower.first < lower.second || higher.first < higher.second) {
        int m1 = (lower.first + lower.second + 1) / 2;
        int m2 = (higher.first + higher.second) / 2;

        cout << "ASK " << m1 << ' ' << m2 << endl;
        string res1, res2; cin >> res1 >> res2;
        if (sw) swap(res1, res2);

        if (res1 == "yes") {
            lower.first = m1;
        } else {
            lower.second = m1 - 1;
        }

        if (res2 == "yes") {
            higher.second = m2;
        } else {
            higher.first = m2 + 1;
        }
    }

    if (sw) swap(lower, higher);
    cout << "GUESS " << lower.first << ' ' << higher.first << endl;

    return 0;
}
