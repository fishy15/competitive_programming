// :pray: :fishy:

#include <iostream>
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

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    double fact = exp(-1);
    for (int i = 1; i <= n; i++) {
        fact *= i;
        int times = (int)(fact) / MOD;
        fact -= MOD * times;
    }

    int ans = (int)(fact + 0.5);
    cout << ans << '\n';
    return 0;
}
