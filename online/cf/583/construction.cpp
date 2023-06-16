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
#define MAXN 100010

using namespace std;

int n;
vector<int> idx[MAXN];
int cur_attach[2 * MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int d; cin >> d;
        idx[d].push_back(i);
    }

    int prev_main = -1;

    int cur_p = 0;
    for (int i = n; i >= 1; i--) {
        for (int x : idx[i]) {
            int main = 2 * x + 1;
            cur_attach[cur_p] = main;

            if (prev_main != -1) {
                cout << main << ' ' << prev_main << '\n';
            }

            prev_main = main;
            cur_p++;
        }
    }

    cur_p = 0;
    for (int i = n; i >= 1; i--) {
        for (int x : idx[i]) {
            int nxt = 2 * x + 2;
            int att = cur_attach[cur_p + i - 1];
            cout << att << ' ' << nxt << '\n';

            if (cur_attach[cur_p + i] == 0) {
                cur_attach[cur_p + i] = nxt;
            }
            cur_p++;
        }
    }

    return 0;
}
