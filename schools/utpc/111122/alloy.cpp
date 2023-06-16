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

    string s;
    cin >> s;

    int n = s.size();

    vector<char> nxt(n);
    char c = -1;
    nxt[n - 1] = -1;
    for (int i = n - 2; i >= 0; i--) {
        if (s[i] != s[i + 1]) {
            c = s[i + 1];
        }
        nxt[i] = c;
    }

    for (int i = 0; i < n; i++) {
        if (s[i] < nxt[i]) {
            cout << s[i] << s[i];
        } else {
            cout << s[i];
        }
    }
    cout << '\n';

    return 0;
}
