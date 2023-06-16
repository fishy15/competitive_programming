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

int n, m;
vector<string> grid;
char c[4] = {'A', 'C', 'G', 'T'};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    // test horizontal lines
    // first line ABAB
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) continue;
            int a = 0;
            int b = 0;
            if (i == a || j == a) a++;
            if (i == a || j == a) a++;
            if (i == a || j == a) a++;
            if (i == b || j == b || a == b) b++;
            for (int k = 0; k < n; k += 2) {
                
            }
        }
    }

    return 0;
}
