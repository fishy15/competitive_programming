// :pray: :steph:
// :pray: :bakekaga:

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
    string s; cin >> s;

    int ans = 0;
    int l = 1, r = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            swap(s[i], s[j]);

            int cur = 0;
            int val = 0;

            int min_val = 0;
            for (char c : s) {
                if (c == '(') {
                    cur++;
                } else {
                    cur--;
                }

                if (cur < min_val) {
                    min_val = cur;
                    val = 1;
                } else if (cur == min_val) {
                    val++;
                }
            }

            /* for (int i = -5; i <= 5; i++) { */
            /*     cout << pos[i + n] << ' '; */
            /* } cout << '\n'; */
            //int val = s[0] == '(' ? pos[n + 1] : pos[n - 1];
            //cout << i << ' ' << j << ' ' << val << '\n';
            if (cur == 0 && val > ans) {
                ans = val;
                l = i + 1;
                r = j + 1;
            }

            swap(s[i], s[j]);
        }
    }

    cout << ans << '\n';
    cout << l << ' ' << r << '\n';
    return 0;
}
