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
#include <random>
#include <chrono>
 
#include <ext/pb_ds/assoc_container.hpp>
 
#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007
 
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
 
// change if necessary
#define MAXN 1000000
 
using namespace std;
using namespace __gnu_pbds;
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct custom_hash {
    size_t operator()(pair<ll, ll> p) const {
        size_t a = splitmix64(p.first);
        size_t b = p.second;
        return a + b;
    }

    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
};
 
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
};
 
array dx{1, 0, -1, 0, 0};
array dy{0, 1, 0, -1, 0};

bool process(ll &sigma2, ld &sigma, const vector<point<ll>> &pts) {
    int n = pts.size();
    gp_hash_table<pair<ll, ll>, vector<point<ll>>, custom_hash> in_box{};
    for (int i = 0; i < n; i++) {
        int x_box = (int) pts[i].x / sigma;
        int y_box = (int) pts[i].y / sigma;
        in_box[{x_box, y_box}].push_back(pts[i]);
 
        for (int j = 0; j < 5; j++) {
            int bx = x_box + dx[j];
            int by = y_box + dy[j];
 
            auto it = in_box.find({bx, by});
            if (it != in_box.end()) {
                for (auto p : it->second) {
                    auto d2 = (pts[i] - p).norm2();
                    if (d2 != 0 && d2 < sigma2) {
                        sigma2 = d2;
                        sigma = sqrt(d2);
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    int n;
    cin >> n;
 
    vector<point<ll>> pts(n);
    for (auto &[x, y] : pts) {
        cin >> x >> y;
    }
 
    shuffle(pts.begin(), pts.end(), rng);
 
    ll sigma2 = (pts[0] - pts[1]).norm2();
    for (int i = 1; i < n - 1; i++) {
        auto d2 = (pts[i] - pts[i + 1]).norm2();
        sigma2 = min(sigma2, d2);
    }

    ld sigma = sqrt(sigma2);

    bool done = false;
    while (!done) {
        done = process(sigma2, sigma, pts);
    }
 
    cout << sigma2 << '\n';
 
    return 0;
}
