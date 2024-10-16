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

    int r, c, k;
    cin >> r >> c >> k;

    for (int i = 0; i < r; i++) {
        string s, t;
        cin >> s >> t;

        if (s.find('-') != string::npos && t.find('*') != string::npos) {
            cout << "N\n";
            return 0;
        }
    }

    cout << "Y\n";

    return 0;
}
