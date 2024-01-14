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
 
template<typename T>
struct point {
    T x, y;
 
    point() : x{}, y{} {}
    point(T x, T y) : x{x}, y{y} {}
 
    point operator+(const point<T> &other) const { return {x + other.x, y + other.y}; }
    point &operator+=(const point<T> &other) { return *this = *this + other; }
    point operator-(const point<T> &other) const { return {x - other.x, y - other.y}; }
    point &operator-=(const point<T> &other) { return *this = *this - other; }

    T norm2() const { return x * x + y * y; }
    ld norm() const { return sqrt(x * x + y * y); }
    T cross(const point<T> &other) { return x * other.y - y * other.x; }
};

template<typename T>
istream &operator>>(istream &in, point<T> &p) {
    return in >> p.x >> p.y;
}

void solve() {
    point<ll> p1, p2, p3;
    cin >> p1 >> p2 >> p3;

    auto c = (p2 - p1).cross(p3 - p2);
    if (c > 0) {
        cout << "LEFT\n";
    } else if (c == 0) {
        cout << "TOUCH\n";
    } else {
        cout << "RIGHT\n";
    }
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
