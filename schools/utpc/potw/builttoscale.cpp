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

vector<int> factor(int x) {
    vector<int> f;
    for (int i = 1; i <= x; i++) {
        if (x % i == 0) {
            f.push_back(i);
        }
    }
    return f;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    auto f = factor(n);
    if ((int) f.size() > 2 && k == 2) {
        cout << f[1] << ' ' << n - 1 << '\n';
    } else {
        if (k <= 2 || k > n - 2) {
            cout << "IMPOSSIBLE\n";
        } else {
            set<int> nums;
            nums.insert(2);
            nums.insert(n - 1);
            nums.insert(n - 2);

            for (int i = 0; i < k - 3; i++) {
                nums.insert(n - 3 - i);
            }

            for (int x : nums) {
                cout << x << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}
