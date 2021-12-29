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
#define MAXN 300010

using namespace std;

int n, m;
string s, t;
int low[MAXN];
int high[MAXN];

int calc(int start) {
    int res = 0;
    int zcnt = (start == 0);

    for (int i = 1; i < (n + m); i++) {
        if (start == 0) {
            if (zcnt + 1 <= high[i]) {
                zcnt++;
            } else {
                res++;
                start = 1;
            }
        } else {
            if (zcnt >= low[i]) {
                // pass
            } else {
                res++;
                start = 0;
                zcnt++;
            }
        }
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    cin >> s;
    cin >> t;

    int scnt = 0;
    int tcnt = 0;
    for (int i = 0; i < (n + m); i++) {
        if (s[i] == '0') {
            scnt++;
        }

        if (t[i] == '0') {
            tcnt++;
        }

        low[i] = min(scnt, tcnt);
        high[i] = max(scnt, tcnt);
    }

    int change = INF;
    if (high[0] == 1) change = min(change, calc(0));
    if (low[0] == 0) change = min(change, calc(1));

    cout << (n + m) - 1 - change << '\n';

    return 0;
}
