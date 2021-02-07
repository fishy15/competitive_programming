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

    int n; cin >> n;

    int l = 1;
    int r = n;

    while (l < r) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        int v1, v2;
        cout << "? " << m1 << endl;
        cin >> v1;

        cout << "? " << m2 << endl;
        cin >> v2;

        if (v1 < v2) {
            r = m2 - 1;
        } else {
            l = m1 + 1;
        }
    }

    cout << "! " << l << endl;

    return 0;
}
