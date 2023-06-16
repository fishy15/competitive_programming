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

    int n; cin >> n;
    map<int, int> cnt;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    int low = cnt.begin()->first;
    int tot_low = low * cnt[low] + (low + 1) * cnt[low + 1];

    if (tot_low < n) {
        cout << "impossible\n";
        return 0;
    }

    if (cnt[100] > 0 && cnt[99] + cnt[100] != n) {
        cout << "impossible\n";
        return 0;
    }

    cout << "possible\n";
    

    return 0;
}
