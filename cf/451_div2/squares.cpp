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

#define MAXN 200000

using namespace std;

struct num {
    int n;
    int to_sq;
    int to_not_sq;

    num() {
        n = 0;
        to_sq = 0;
        to_not_sq = 0;
    }

    num(int n) {
        this->n = n;
        int sq = (int)(sqrt(n));
        if (n == 0) {
            to_sq = 0;
            to_not_sq = 2;
        } else if (sq * sq == n) {
            to_sq = 0;
            to_not_sq = 1;
        } else {
            to_sq = min(n - sq * sq, (sq + 1) * (sq + 1) - n);
            to_not_sq = 0;
        }
    }
};

int n;
num nums[MAXN];

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums[i] = num(x);
    }

    sort(nums, nums + n, [](const num &n1, const num &n2) {
        if (n1.to_sq == n2.to_sq) {
            return n1.to_not_sq > n2.to_not_sq;
        }

        return n1.to_sq < n2.to_sq;
    });

    ll ans = 0;
    for (int i = 0; i < n / 2; i++) {
        ans += nums[i].to_sq;
        //cerr << "to sq: " << nums[i].n << '\n';
    }

    for (int i = n / 2; i < n; i++) {
        ans += nums[i].to_not_sq;
        //cerr << "to not sq: " << nums[i].n << '\n';
    }

    cout << ans << '\n';

    return 0;
}