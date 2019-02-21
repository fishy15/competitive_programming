#include <iostream>
#include <fstream>
#include <vector>

#define ll long long 

using namespace std;

vector<vector<ll>> res;

ll calc(int, int);

int main() {
    ifstream fin("gradina3.in");
    ofstream fout("gradina3.out");

    ll n, k, p; fin >> n >> p >> k;
    vector<vector<bool>> orchard(n, vector<bool>(n, false));
    for (ll i = 0; i < n; i++) {
        ll x, y; fin >> x >> y;
        orchard[x - 1][y - 1] = true;
    }

    /*
    for (auto v : orchard) {
        for (auto i : v) {
            cout << i << ' ';
        }

        cout << endl;
    }
    */

    /*
    cout << endl;
    for (auto v : rows) {
        for (auto i : v) {
            cout << i << ' ';
        }

        cout << endl;
    }
    */

    res = vector<vector<ll>>(n, vector<ll>(n, 0));
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            //cout << x << ' ' << y << endl;
            ll val1 = 0;
            if (x > 0) {
                val1 = res[x - 1][y];
            }

            ll val2 = 0;
            if (y > 0) {
                val2 = res[x][y - 1];
            }

            ll val3 = 0;
            if (x > 0 && y > 0) {
                val3 = res[x - 1][y - 1];
            }

            res[x][y] = val1 + val2 - val3 + orchard[x][y]; 
        }
    }

    /* 
    cout << endl;
    for (auto v : res) {
        for (auto i : v) {
            cout << i << ' ';
        }

        cout << endl;
    }
    */ 

    ll max = 0;
    ll count = 0;
    for (ll i = k - 1; i < n; i++) {
        for (ll j = k - 1; j < n; j++) {
            ll val = calc(i, j) - calc(i - k, j) - calc(i, j - k) + calc(i - k, j - k);
            if (val > max) {
                max = val;
                count = 1;
            } else if (val == max) {
                count++;
            }
        }
    }

    /*
    for (ll i = k; i <= n; i++) {
        for (ll j = k; j <= n; j++) {
            ll val = res[i][j] - res[i - k][j] - res[i][j - k] + res[i - k][j - k];
            if (val == max) {
                cout << i << ' ' << j << ' ' << res[i][j] << ' ' << res[i - k][j - k] << endl;
            }
        }
    }
    */

    fout << max << '\n' << count << '\n';
    return 0;
}

ll calc(int x, int y) {
    if (x == -1 || y == -1) {
        return 0;
    }

    return res[x][y];
}
