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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

char diff(char a, char b, char c) {
    char res = 'A';
    while (res == a || res == b || res == c) {
        res++;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    rep(i, 0, n) {
        cin >> grid[i];
    }

    rep(i, 0, n) {
        rep(j, 0, m) {
            char a = grid[i][j];
            char b = i > 0 ? grid[i-1][j] : a;
            char c = j > 0 ? grid[i][j-1] : a;
            grid[i][j] = diff(a, b, c);
        }
    }

    rep(i, 0, n) {
        cout << grid[i] << '\n';
    }

    return 0;
}
