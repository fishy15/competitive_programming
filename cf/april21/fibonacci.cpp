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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s; cin >> s;
    int n = s.size();

    for (int i = 0; i < n - 2; i++) {
        char nxt = (s[i] + s[i + 1] - 2 * 'A') % 26 + 'A';
        if (nxt != s[i + 2]) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";

    return 0;
}
