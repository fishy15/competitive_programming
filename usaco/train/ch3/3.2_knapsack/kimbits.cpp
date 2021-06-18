/*
ID: aaryan.1
TASK: kimbits
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define ll long long

using namespace std;

ll choose[32][32];

void make_table() {
    for (int n = 0; n < 32; n++) {
        choose[n][0] = 1;

        for (int k = 1; k < 32; k++) {
            choose[n][k] = choose[n][k - 1] * (n - k + 1) / k;
        }
    }
}

string calc(int n, int l, ll i) {
    //cout << n << ' ' << l << ' ' << i << endl;

    if (n == 0) {
        return "";
    }

    if (l == 0) {
        return "0" + calc(n - 1, 0, 0);
    }

    ll less = 0;
    for (int j = 0; j <= l; j++) {
        less += choose[n - 1][j];
    }
    //cout << less << '\n';

    if (i > less) {
        return "1" + calc(n - 1, l - 1, i - less);
    } else {
        return "0" + calc(n - 1, l, i);
    }
}

int main() {
    ifstream fin("kimbits.in");
    ofstream fout("kimbits.out");

    make_table();

    int n, l; ll i; fin >> n >> l >> i;
    fout << calc(n, l, i) << '\n';
    return 0;
}