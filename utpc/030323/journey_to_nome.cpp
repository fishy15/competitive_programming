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

    int n, m;
    cin >> n >> m;
    swap(n, m); // oops

    vector<int> rel_prime;
    rel_prime.reserve(n);

    for (int i = 1; i < n; i++) {
        if (gcd(i, n) == 1) {
            rel_prime.push_back(i);
        }
    }

    int num = rel_prime.size();

    while (m--) {
        ll a;
        cin >> a;
        a--;

        ll ans = rel_prime[a % num] + n * (a / num);
        cout << ans << ' ';
    }

    cout << '\n';


    return 0;
}
