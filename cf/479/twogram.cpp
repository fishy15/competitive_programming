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

    int n; string s; cin >> n >> s;
    string ans;
    int m = 0;
    for (char a = 'A'; a <= 'Z'; a++) {
        for (char b = 'A'; b <= 'Z'; b++) {
            string s2 = "  ";
            s2[0] = a;
            s2[1] = b;
            int cnt = 0;
            for (int i = 0; i < n - 1; i++) {
                if (s2 == s.substr(i, 2)) {
                    cnt++;
                }
            }
            if (cnt > m) {
                ans = s2;
                m = cnt;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
