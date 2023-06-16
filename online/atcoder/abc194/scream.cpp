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

    int a, b; cin >> a >> b;
    a += b;
    if (a >= 15 && b >= 8) {
        cout << 1 << '\n';
    } else if (a >= 10 && b >= 3) {
        cout << 2 << '\n';
    } else if (a >= 3) {
        cout << 3 << '\n';
    } else {
        cout << 4 << '\n';
    }

    return 0;
}
