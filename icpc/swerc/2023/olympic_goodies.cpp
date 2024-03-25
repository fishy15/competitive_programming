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

    int n, p;
    cin >> n >> p;

    vector<int> deg(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        deg[a]++;
        deg[b]++;
    }

    if (n == 1) {
        // sane default
        cout << "0\n";
        return 0;
    }

    auto leaves = count(deg.begin(), deg.end(), 1);
    int base = p / leaves;
    int rem = p % leaves;
    cout << 2 * base + min(2, rem) << '\n';

    return 0;
}
