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
#define MAXN 200010

using namespace std;

int n;
int nums[MAXN];
int bit[MAXN];

void upd(int x, int v) {
    while (x < MAXN) {
        bit[x] += v;
        x += x & -x;
    }
}

int bsearch(int x) {
    int pos = 0;
    int sum = 0;
    for (int i = 17; i >= 0; i--) {
        if (pos + (1 << i) <= n && sum + bit[pos + (1 << i)] < x) {
            sum += bit[pos + (1 << i)];
            pos += 1 << i;
        }
    }
    return pos + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
        upd(i, 1);
    }

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        int pos = bsearch(x);
        cout << nums[pos] << ' ';
        upd(pos, -1);
    }
    cout << '\n';

    return 0;
}
