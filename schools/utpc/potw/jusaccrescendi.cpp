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

bool test(int t, array<int, 4> combo) {
    // find non collinear points
    ll p = 1999;
    vector<pair<int, int>> pts;

    for (int x = 0; x < p; x++) {
        int a = x % p;
        int b = x * x % p;

        if (a % 2 == 0) {
            if (b % 2 == 0) {
                if (combo[0] > 0) {
                    pts.push_back({a, b});
                    combo[0]--;
                }
            } else {
                if (combo[1] > 0) {
                    pts.push_back({a, b});
                    combo[1]--;
                }
            }
        } else {
            if (b % 2 == 0) {
                if (combo[2] > 0) {
                    pts.push_back({a, b});
                    combo[2]--;
                }
            } else {
                if (combo[3] > 0) {
                    pts.push_back({a, b});
                    combo[3]--;
                }
            }
        }
    }

    if ((int) pts.size() == t) {
        for (auto [x, y] : pts) {
            cout << x - 1000 << ' ' << y - 1000 << '\n';
        }

        return true;
    } else {
        return false;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t, b;
    cin >> t >> b;

    // ee, eo, oe, oo
    array<int, 4> combo;

    int count = 0;
    for (int w = 0; w <= t; w++) {
        for (int x = 0; w + x <= t; x++) {
            for (int y = 0; w + x + y <= t; y++) {
                int z = t - (w + x + y);
                ll ok_triangles = t * (t - 1) * (t - 2) / 6 
                                - w * x * y
                                - w * x * z
                                - w * y * z
                                - x * y * z;

                if (ok_triangles == b) {
                    combo = {w, x, y, z};

                    if (test(t, combo)) {
                        return 0;
                    } else {
                        count++;
                        if (count == 200) {
                            goto done;
                        }
                    }
                }
            }
        }
    }

done:
    cout << "IMPOSSIBLE\n";

    return 0;
}
