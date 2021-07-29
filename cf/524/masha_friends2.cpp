#include <iostream>

typedef long long ll;
using namespace std;

ll white_under(bool white_corner, ll x, ll y) {
    if (white_corner) {
        if (x % 2 == 0 || y % 2 == 0) {
            return x * y / 2;
        } else {
            return x * y / 2 + 1;
        }
    } else {
        return x * y - white_under(true, x, y);
    }
}

ll black_under(bool white_corner, ll x, ll y) {
    return x * y - white_under(white_corner, x, y);
}

bool white_corner(ll x, ll y) {
    return (x + y) % 2 == 0;
}

ll min(ll x, ll y) {
    return x < y ? x : y;
}

ll max(ll x, ll y) {
    return x > y ? x : y;
}

int main() {
    ll n; cin >> n;
    for (ll i = 0; i < n; i++) {
        ll w, h; cin >> w >> h;
        ll white[4];
        ll black[4];

        for (ll i = 0; i < 4; i++) {
            cin >> white[i];
            white[i]--;
        }

        white[2]++;
        white[3]++;

        for (ll i = 0; i < 4; i++) {
            cin >> black[i];
            black[i]--;
        }

        black[2]++;
        black[3]++;

        ll whiteTotal = white_under(true, w, h);
        //cout << "init: " << whiteTotal << endl;
        // remove blacks in white pall part
        //cout << "corner: " << white_corner(white[0], white[1]) << endl;
        //cout << "add: " << white_under(white_corner(white[0], white[1]), white[2] - white[0], white[3] - white[1]);

        whiteTotal += black_under(white_corner(white[0], white[1]), white[2] - white[0], white[3] - white[1]);

        //cout << "white: " << whiteTotal << endl;
        // remove white in black pall part
        whiteTotal -= white_under(white_corner(black[0], black[1]), black[2] - black[0], black[3] - black[1]);
        //cout << "black: " << whiteTotal << endl;
        // remove white in overlap part
        ll inter[4];
        inter[0] = max(white[0], black[0]);
        inter[1] = max(white[1], black[1]);
        inter[2] = min(white[2], black[2]);
        inter[3] = min(white[3], black[3]);

        if (inter[3] > inter[1] && inter[2] > inter[0]) {
            whiteTotal -= black_under(white_corner(inter[0], inter[1]), inter[2] - inter[0], inter[3] - inter[1]);
        }

        cout << whiteTotal << ' ' << w * h - whiteTotal << '\n';
    }
}
