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

template<typename T>
T twice_area(const vector<point<T>> &polygon) {
    int n = polygon.size();
    T area{};
    for (int i = 0; i < n; i++) {
        int nxt = (i == n - 1) ? 0 : i + 1;
        area += polygon[i].x * polygon[nxt].y - polygon[i].y * polygon[nxt].x;
    }
    return abs(area);
}

template<typename T,
         typename std::enable_if_t<std::is_integral<T>::value, T> * = nullptr>
T lattice_points(const vector<point<T>> &polygon) {
    int n = polygon.size();
    T ans{};
    for (int i = 0; i < n; i++) {
        auto nxt = (i == n - 1) ? 0 : i + 1;
        auto vec = polygon[i] - polygon[nxt];
        ans += gcd(vec.x, vec.y);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    int n;
    cin >> n;

    vector<point<ll>> polygon(n);
    for (auto &p : polygon) {
        cin >> p;
    }

    auto area2 = twice_area(polygon);
    auto b = lattice_points(polygon);
    auto i = (area2 - b + 2) / 2;

    cout << i << ' ' << b << '\n';

    return 0;
}
