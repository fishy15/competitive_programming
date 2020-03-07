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
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    string s; cin >> s;

    int l = 0;
    int r = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') l++;
        else r++;
    }

    if (l != r) {
        cout << "-1\n";
        return 0;
    }

    int prev = 0;
    int cur = 0;
    l = 0;

    int ans = 0;
    
    for (int i = 0; i < n; i++) {
        if (cur == 0) {
            if (prev == -1) ans += i - l;
            l = i;
        }

        prev = cur;

        if (s[i] == '(') {
            cur++;
        } else {
            cur--;
        }

    }

    if (cur == 0 && prev == -1) {
        ans += n - l;
    }

    cout << ans << '\n';

    return 0;
}
