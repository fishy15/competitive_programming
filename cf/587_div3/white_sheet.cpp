// :pray: :fishy:

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct rect {
    int x1, x2, y1, y2;

    bool inside(double x, double y) {
        return (x1 <= x && x <= x2) && (y1 <= y && y <= y2);
    }
};

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    rect white, black1, black2;
    cin >> white.x1 >> white.y1 >> white.x2 >> white.y2;
    cin >> black1.x1 >> black1.y1 >> black1.x2 >> black1.y2;
    cin >> black2.x1 >> black2.y1 >> black2.x2 >> black2.y2;

    for (double i = white.x1; i <= white.x2; i += 0.5) {
        if (!black1.inside(i, white.y1) && !black2.inside(i, white.y1)) {
            cout << "YES\n";
            return 0;
        }

        if (!black1.inside(i, white.y2) && !black2.inside(i, white.y2)) {
            cout << "YES\n";
            return 0;
        }
    }

    for (double j = white.y1; j <= white.y2; j += 0.5) {
        if (!black1.inside(white.x1, j) && !black2.inside(white.x1, j)) {
            cout << "YES\n";
            return 0;
        }

        if (!black1.inside(white.x2, j) && !black2.inside(white.x2, j)) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";

    return 0;
}
