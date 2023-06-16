// :pray: :arrayman:
// :pray: :summitosity:
// :pray: :pusheenosity:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk-duk-go:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eediosity:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinxiosity
// :pray: :eggyosity:
// :pray: :squares-are-fine:
// :pray: :see-jay:
// :pray: :stephiosity:
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

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 10000007

using namespace std;

bool is_prime(int p) {
    if (p % 2 == 0 && p != 2) return false;
    int cur = 3;
    while (cur <= sqrt(p)) {
        if (p % cur == 0) return false;
        cur += 2;
    }

    return true;
}

int r(int n) {
    string s1 = to_string(n);
    string ans = "";
    for (int i = s1.size() - 1; i >= 0; i--) {
        ans += s1[i];
    }

    return stoi(ans);
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        int rev = r(p);
        if (p != rev && is_prime(p) && is_prime(rev)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}