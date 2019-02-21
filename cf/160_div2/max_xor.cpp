#include <iostream>
#include <fstream>

#define ll long long

using namespace std;

ll calcVal(ll l, ll r) {
    ll maxPow = 1;

    while (maxPow < r) {
        maxPow <<= 1;
    }
}

int main() {
    ll l, r; cin >> l >> r;
    cout << calcVal(l, r) << '\n';
}