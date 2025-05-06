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

#ifdef LOCAL
constexpr int T = 1000;
int dollars = 1000;
int rnd = 0;
int last_b;

pair<int, int> get() {
    if (rnd >= T) {
        cout << "LOSE" << dollars << endl;
        exit(0);
    }

    int b = rand() % dollars + 1;
    last_b = b;
    cout << "ROUND " << dollars << ' ' << b << '\n';
    return {dollars, b};
}

void move(bool play) {
    rnd++;
    if (play) {
        if (rand() % 2) {
            dollars += 2 * last_b;
        } else {
            dollars -= last_b;
        }

        if (dollars >= 10'000) {
            cout << "WIN\n";
            exit(0);
        }
    }
}

#else
pair<int, int> get() {
    string s;
    cin >> s;

    if (s == "WIN" || s == "LOSE") {
        exit(0);
    } else {
        int x, y;
        cin >> x >> y;
        return {x, y};
    }
}

void move(bool play) {
    if (play) {
        cout << "PLAY" << endl;
    } else {
        cout << "SKIP" << endl;
    }
}
#endif

bool decision(int d, int b) {
    return 4 * b < d;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

#ifdef LOCAL
    srand(t);
#endif

    while (true) {
        auto [d, b] = get();
        move(decision(d, b));
    }

    return 0;
}
