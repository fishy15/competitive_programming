// :pray: :arrayman:
// :pray: :summit:
// :pray: :pusheen:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eed:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinx:
// :pray: :eyg:
// :pray: :evan:
// :pray: :cj:
// :pray: :steph:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:
// :pray: :wayne:
// :pray: :wu:
// :pray: :vmaddur:
// :pray: :dorijanko:
// :pray: :gaming:
// :pray: :kassuno:
// :pray: :hyacinth:
// :pray: :chilli:
// :pray: :dhruv:
// :pray: :philip:
// :pray: :paiman:
// :pray: :camel:
// :pray: :tree:
// :pray: :tux:
// :pray: :jony:
// :pray: :kage:

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 10000007

using namespace std;

class BIT {
public:
    vector<ll> bit;
    
    ll get_max_one(ll n) {
        return n & (~n + 1);
    }

    BIT(ll sz) {
        bit = vector<ll>(sz + 1, 0);
    }

    ll get_before(ll i) {
        ll sum = 0;
        
        while (i > 0) {
            sum += bit[i];
            i -= get_max_one(i);
        }

        return sum;
    }

    void add(ll i, ll val) {
        while (i < bit.size()) {
            bit[i] += val;
            i += get_max_one(i);
        }
    }
};

ll n, m;
ll q;
vector<BIT> bits;
vector<ll> curVal;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> m;

    curVal = vector<ll>(n + 1);
    for (ll i = 0; i < m; i++) {
        bits.push_back(BIT(n));
    }

    for (ll i = 0; i < n; i++) {
        ll x; cin >> x;
        bits[x % m].add(i + 1, x);
        curVal[i + 1] = x;
    }

    cin >> q;
    for (ll i = 0; i < q; i++) {
        char c; cin >> c;
        if (c == '+') {
            ll p, r;
            cin >> p >> r;
            ll val = curVal[p];
            bits[val % m].add(p, -val);
            curVal[p] += r;
            val += r;
            bits[val % m].add(p, val);
            cout << val << '\n';
        } else if (c == '-') {
            ll p, r;
            cin >> p >> r;
            ll val = curVal[p];
            if (val >= r) {
                bits[val % m].add(p, -val);
                curVal[p] -= r;
                val -= r;
                bits[val % m].add(p, val);
            }
            cout << val << '\n';
        } else {
            ll l, r, mod;
            cin >> l >> r >> mod;
            cout << bits[mod].get_before(r) - bits[mod].get_before(l - 1) << '\n';
        }
    }

    return 0;
}
