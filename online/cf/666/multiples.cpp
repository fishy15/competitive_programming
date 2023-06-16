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
#define MAXN 100010

using namespace std;

int n;
ll nums[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> nums[i];

    if (n == 1) {
        cout << "1 1\n";
        cout << -nums[0] << '\n';
        cout << "1 1\n";
        cout << 0 << '\n';
        cout << "1 1\n";
        cout << 0 << '\n';
        return 0;
    }

    // all n
    cout << 1 << ' ' << n << '\n';
    for (int i = 0; i < n - 1; i++) {
        ll mm = (nums[i] % (n - 1) + (n - 1)) % (n - 1);
        mm = ((n - 1) - mm) % (n - 1);
        cout << mm * n << ' ';
        nums[i] += mm * n;
    }

    cout << "0\n";
    
    // first n - 1
    cout << 1 << ' ' << n - 1 << '\n';
    for (int i = 0; i < n - 1; i++) {
        cout << -nums[i] << ' ';
    }
    cout << '\n';

    // last one
    cout << n << ' ' << n << '\n';
    cout << -nums[n - 1] << '\n';

    return 0;
}
