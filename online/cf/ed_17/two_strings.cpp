// :pray: :steph:
// :pray: :bakekaga:

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
#define MAXN 100000

using namespace std;

string a, b;
int n, m;
int pos[MAXN];
int pos2[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> a >> b;
    n = (int)(a.size());
    m = (int)(b.size());

    int x = 0;
    for (int i = 0; i < m; i++) {
        while (x < n && a[x] != b[i]) {
            x++;
        }
        pos[i] = min(n, x++);
    }

    x = n - 1;
    for (int i = m - 1; i >= 0; i--) {
        while (x >= 0 && a[x] != b[i]) {
            x--;
        }
        pos2[i] = max(-1, x--);
    }

    x = 1;
    int ans1 = -1;
    int ans2 = m;
    for (int i = 0; i < m; i++) {
        if (pos[i] == n) break;
        while (x < m && pos[i] >= pos2[x]) {
            x++;
        }
        if (x - i < ans2 - ans1) {
            ans1 = i;
            ans2 = x;
        }
    }

    int pos1 = 0;
    while (pos1 < m && pos[pos1] < n) pos1++;
    pos1--;
    int pos3 = m - 1;
    while (pos3 >= 0 && pos2[pos3] >= 0) pos3--;
    pos3++;

    if (m - pos1 < ans2 - ans1) {
        ans1 = pos1;
        ans2 = m;
    }

    if (pos3 + 1 < ans2 - ans1) {
        ans1 = -1;
        ans2 = pos3;
    }

    //cout << ans1 << ' ' << ans2 << '\n';
    if (ans1 >= ans2) {
        cout << b << '\n';
    } else if (ans2 - ans1 - 1 == m) {
        cout << "-\n";
    } else {
        cout << b.substr(0, ans1 + 1) << b.substr(ans2, m - ans2) << '\n';
    }

    /* for (int i = 0; i < m; i++) { */
    /*     cout << pos[i] << ' '; */
    /* } cout << '\n'; */
    /* for (int i = 0; i < m; i++) { */
    /*     cout << pos2[i] << ' '; */
    /* } cout << '\n'; */

    return 0;
}
