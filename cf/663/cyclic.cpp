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
    ll pp = 1;
    for (int i = 0; i < n - 1; i++) {
        pp *= 2;
        pp %= MOD;
    }

    ll fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
        fact %= MOD;
    }

    cout << (fact - pp + MOD) % MOD << '\n';

    return 0;
}
