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

int n, m;
string s;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    cin >> s;

    for (int i = 1; i <= n; i++) {
        bool ok = true;
        for (int j = i; j < n; j++) {
            if (s[j] != s[j % i]) {
                ok = false;
                break;
            }
        }

        if (ok) {
            for (int j = 0; j < m; j++) {
                cout << s[(n + j) % i];
            }
            cout << '\n';
            return 0;
        }
    }

    return 0;
}
