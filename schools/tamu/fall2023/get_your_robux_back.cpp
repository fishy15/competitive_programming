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

    string cur(20, 'a');
    for (int i = 0; i < 20; i++) {
        pair<int, char> best = {INF, ' '};
        for (char c = 'a'; c <= 'z'; c++) {
            cur[i] = c;
            cout << cur << endl;
            int res;
            cin >> res;
            best = min(best, {res, c});
        }
        cur[i] = best.second;
    }

    return 0;
}
