/*
 * Note that the segment of numbers that are >k are all next to each other, they start at p+1, and the segment
 * will at max have a length of n / 2. This means that after the first sqrt(n) moves, we can check each 
 * sqrt(n) block for a number > k. After this, we can binary search for the first number that is > k, and the
 * previous index of that is p.
 */
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

int n, k;
int sq;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    sq = (int)(sqrt(n));

    // waste first sqrt(x) moves
    for (int i = 0; i < sq; i++) {
        cout << "? 1" << endl;
        int x; cin >> x;
    }

    int cur = -1;
    for (int st = 1; st <= sq; st++) {
        for (int i = st; i <= n; i += sq) {
            cout << "? " << i << endl;
            int x; cin >> x;
            if (x > k) {
                cur = i;
                break;
            }
        }
        if (cur != -1) break;
    }

    for (int i = 18; i >= 0; i--) {
        int pos = cur - (1 << i);
        pos %= n;
        if (pos <= 0) pos += n;

        cout << "? " << pos << endl;
        int x; cin >> x;
        if (x > k) cur = pos;
    }

    cur--;
    if (cur <= 0) cur += n;

    cout << "! " << cur << endl;

    return 0;
}
