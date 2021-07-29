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

int n, a;
vector<double> deg;
double bb;
int ans = 1;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> a;

    for (int i = 1; i < n - 1; i++) {
        double val = 180.0 * i / n;
        if (fabs(val - a) < fabs(bb - a)) {
            bb = val;
            ans = i;
        }
    }

    cout << 2 << ' ' << 1 << ' ' << 2 + ans << '\n';
    return 0;
}
