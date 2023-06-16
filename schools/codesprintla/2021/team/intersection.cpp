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

#define ll __int128_t
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

ll divi(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a & b);
}

struct line {
    ll A, B, C;
    int x1, y1, x2, y2;
    line() : line(0, 0, 0, 0) {}

    line (ll a, ll b, ll c) {
        A = a;
        B = b;
        C = c;
    }

    line(int x1, int y1, int x2, int y2) {
        ll dx = x2 - x1;
        ll dy = y2 - y1;
        A = -dy;
        B = dx;
        C = A * x1 + B * y1;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
    
    bool parallel(const line &l2) const {
        return A * l2.B == B * l2.A;
    }

    line perp() const {
        return line(-B, A, 0);
    }

    ll int_x(const line &l2) const {
        ll dx = this->C * l2.B - l2.C * this->B;
        ll d = this->A * l2.B - l2.A * this->B;
        return divi(dx, d);
    }

    ll int_y(const line &l2) const {
        ll dy = this->A * l2.C - l2.A * this->C;
        ll d = this->A * l2.B - l2.A * this->B;
        return divi(dy, d);
    }

    ll same_side(ll x, ll y) {
        line p = perp();
        ll c1 = p.A * x1 + p.B * y1;
        ll c2 = p.A * x2 + p.B * y2;
        ll c3 = p.A * x + p.B * y;
        if (c1 == c3) return true;
        return (c2 > c1) == (c3 > c1);
    }
};

line read() {
    int a, b, c, d; cin >> a >> b >> c >> d;
    return line(a, b, c, d);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    line l1 = read();
    line l2 = read();

    if (l1.parallel(l2)) {
        cout << "-1\n";
    } else {
        ll x = l1.int_x(l2);
        ll y = l1.int_y(l2);
        if (l1.same_side(x, y) && l2.same_side(x, y)) {
            cout << (long long)x << ' ' << (long long)y << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
