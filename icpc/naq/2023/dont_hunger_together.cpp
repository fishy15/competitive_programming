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
#define eps 1e-11
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<array<int, 2>> days(n);
    for (auto &[x, y] : days) {
        cin >> x >> y;
        y--;
    }

    // x = total amount of food consumed on day x
    auto check = [&](ld x) {
        map<int, ld> food;

        for (int i = 0; i < n; i++) {
            auto [q, f] = days[i];
            food[f] += q;

            ld needed = x;
            while (needed >= eps) {
                if (food.empty()) return false;
                else {
                    auto it = food.begin();
                    if (it->second <= needed) {
                        needed -= it->second;
                        food.erase(it);
                    } else {
                        it->second -= needed;
                        needed = 0;
                    }
                }
            }

            auto it = food.find(i);
            if (it != food.end()) {
                food.erase(it);
            }
        }

        return true;
    };

    ld l = 0;
    ld r = INFLL;
    ld ans = -1;

    for (int i = 0; i < 200; i++) {
        ld m = l + (r - l) / 2;
        if (m < eps) break;
        if (check(m)) {
            ans = m;
            l = m;
        } else {
            r = m;
        }
    }

    if (ans < 0) {
        cout << "-1\n";
    } else {
        ld ansd = (ld) ans / k;
        cout << fixed << setprecision(15) << ansd << '\n';
    }

    return 0;
}
