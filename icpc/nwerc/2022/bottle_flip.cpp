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
#define eps 1e-10
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

template<typename F>
ld gss(ld a, ld b, F f) {
    ld r = (sqrt(5)-1)/2;
    ld x1 = b - r*(b-a), x2 = a + r*(b-a);
    ld f1 = f(x1), f2 = f(x2);
    while (b-a > eps)
        if (f1 < f2) {
            b = x2; x2 = x1; f2 = f1;
            x1 = b - r*(b-a); f1 = f(x1);
        } else {
            a = x1; x1 = x2; f1 = f2;
            x2 = a + r*(b-a); f2 = f(x2);
        }
    return a;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int h, r, da, dw;
    cin >> h >> r >> da >> dw;

    auto x = gss(0, h, [&](ld x) {
        x /= h;
        auto num = (ld) (dw - da) * x * x + da;
        auto denom = (ld) (dw - da) * x + da;
        return num / denom;
    });

    cout << fixed << setprecision(20);
    cout << x << '\n';

    return 0;
}
