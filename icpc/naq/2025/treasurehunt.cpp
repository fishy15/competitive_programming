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

int ans_x, ans_y;

bool ask(int x, int y) {
    cout << "? " << x << ' ' << y << endl;
#ifdef LOCAL
    if (x == ans_x || x == ans_x + 1) {
        if (y == ans_y || y == ans_y + 1) {
            return true;
        }
    }
    return false;
#else
    int res;
    cin >> res;
    if (res == -1) exit(0);
    return res == 1;
#endif
}

void answer(int x, int y) {
    cout << "! " << x << ' ' << y << endl;
#ifdef LOCAL
    if (ans_x == x && ans_y == y) {
        cout << "GOOD\n";
    } else {
        cout << "BAD\n";
    }
#endif
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

#ifdef LOCAL
    cin >> ans_x >> ans_y;
#endif

    bool a = ask(2, 2);
    bool b = ask(2, 4);
    bool c = ask(4, 2);

    pair<int, int> quadrant;
    if (a) quadrant = {1, 1};
    else if (b) quadrant = {1, 3};
    else if (c) quadrant = {3, 1};
    else quadrant = {3, 3};

    bool down = ask(quadrant.first + 1, quadrant.second);
    bool right = ask(quadrant.first, quadrant.second + 1);
    if (down && right) {
        answer(quadrant.first, quadrant.second);
    } else if (down) {
        answer(quadrant.first + 1, quadrant.second);
    } else if (right) {
        answer(quadrant.first, quadrant.second + 1);
    } else {
        answer(quadrant.first + 1, quadrant.second + 1);
    }

    return 0;
}
