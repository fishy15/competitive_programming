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

using namespace std;

using ll = long long;

ll max_set(ll x) {
    return 1LL << (63 - __builtin_clzll(x));
}

void add_to_basis(vector<ll> &basis, ll a) {
    for (auto x : basis) {
        if (a != 0 && max_set(x) == max_set(a)) {
            a ^= x;
        }
    }

    if (a != 0) {
        basis.push_back(a);
        sort(basis.begin(), basis.end(), greater<>());
    }
}

void print_in_range(const vector<ll> &basis_left, ll l, ll r, ll cur_l, ll cur_r, ll prefix) {
    if (r <= cur_l || cur_r <= l) return;
    if (basis_left.empty()) {
        cout << prefix << ' ';
    } else {
        const auto basis_vector = basis_left[0];
        vector rest(basis_left.begin() + 1, basis_left.end());

        ll cur_m = cur_l + (cur_r - cur_l) / 2;
        if (prefix & max_set(basis_vector)) {
            print_in_range(rest, l, r, cur_l, cur_m, prefix ^ basis_vector);
            print_in_range(rest, l, r, cur_m, cur_r, prefix);
        } else {
            print_in_range(rest, l, r, cur_l, cur_m, prefix);
            print_in_range(rest, l, r, cur_m, cur_r, prefix ^ basis_vector);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    ll l, r;
    cin >> n >> l >> r;
    l--;

    vector<ll> basis;
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        add_to_basis(basis, a);
    }

    ll in_subspace_count = 1LL << basis.size();
    print_in_range(basis, l, r, 0, in_subspace_count, 0);
    cout << '\n';

    return 0;
}
