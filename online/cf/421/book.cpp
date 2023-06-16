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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int c, v0, v1, a, l;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> c >> v0 >> v1 >> a >> l;

    int tot = 0;
    int day = 0;
    while (true) {
        day++;
        tot += v0;
        if (tot >= c) {
            cout << day << '\n';
            return 0;
        }
        tot -= l;
        v0 += a;
        v0 = min(v0, v1);
    }

    return 0;
}
