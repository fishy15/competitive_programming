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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll a, b, x, y;
    cin >> a >> b >> x >> y;

    vector<ll> in_each;
    in_each.push_back(1);

    while (in_each.back() < max(x, y)) {
        if (in_each.size() % 2 == 1) {
            in_each.push_back(in_each.back() * a);
        } else {
            in_each.push_back(in_each.back() * b);
        }
    }

    vector<ll> leq_floor(in_each.size());
    partial_sum(in_each.begin(), in_each.end(), leq_floor.begin());

    auto get_floor = [&](int pos) {
        for (int i = 0; i < (int) leq_floor.size(); i++) {
            if (pos < leq_floor[i]) {
                return i;
            }
        }

        return (int) leq_floor.size();
    };

    auto x_floor = get_floor(x);
    auto y_floor = get_floor(y);

    if (x_floor < y_floor) {
        swap(x, y);
        swap(x_floor, y_floor);
    }

    auto move_down = [&leq_floor, a, b](ll &cur, int &floor) {
        int pos_on_floor = cur - leq_floor[floor - 1]; 
        if (floor % 2 == 0) {
            pos_on_floor /= b;
        } else {
            pos_on_floor /= a;
        }

        auto before = floor == 1 ? 0 : leq_floor[floor - 2];
        cur = before + pos_on_floor;
        floor -= 1;
    };

    while (x_floor > y_floor) {
        move_down(x, x_floor);
    }

    while (x != y) {
        move_down(x, x_floor);
        move_down(y, y_floor);
    }

    cout << x << '\n';

    return 0;
}
