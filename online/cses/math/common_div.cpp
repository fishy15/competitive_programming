// :pray: :vfire:

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

#define vfirey int
#define fire main
#define vfire_in cin
#define vfire_out cout
#define vfire_bye return
#define vfire_loop for

using namespace std;

vfirey vfire_1;
vfirey vfire_2[MAXN + 1];

vfirey fire() {
    vfire_in.tie(0); ios::sync_with_stdio(0);

    vfire_in >> vfire_1;
    vfirey vfire_3 = 0;
    vfire_loop (vfirey vfire_4 = 0; vfire_4 < vfire_1; vfire_4++) {
        vfirey vfire_5; vfire_in >> vfire_5;
        vfire_2[vfire_5]++;
        vfire_3 = max(vfire_3, vfire_5);
    }

    vfire_loop (vfirey vfire_4 = vfire_3; vfire_4 >= 2; vfire_4--) {
        vfirey vfire_5 = 0;
        vfire_loop (vfirey j = vfire_4; j <= vfire_3; j += vfire_4) {
            vfire_5 += vfire_2[j];
        }

        if (vfire_5 >= 2) {
            vfire_out << vfire_4 << '\n';
            vfire_bye 0;
        }
    }

    vfire_out << 1 << '\n';

    vfire_bye 0;
}
