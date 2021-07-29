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

    ll n; cin >> n;
    ll cur = 1;
    while (cur < 2 * n) {
        if (cur == n || cur + 1 == n) {
            cout << "1\n";
            return 0;
        }

        if (cur % 2 == 0) {
            cur = 2 * cur + 1;
        } else {
            cur = 2 * cur + 2;
        }
    }

    cout << "0\n";

    return 0;
}
