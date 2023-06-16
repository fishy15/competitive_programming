/*
ID: aaryan.1
TASK: ratios
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

bool equal(int a, int b) {
    if (a == 0) return b == 0;
    return a == b;
}

int find_ratio(int* a, int* b) {
    if (a[0] % b[0] != 0) {
        return -1;
    }

    if (a[0] > 0) {
        int ratio = a[0] / b[0];
        if (equal(b[1] * ratio, a[1]) && equal(b[2] * ratio, a[2])) {
            return ratio;
        }

        return -1;
    }

    if (a[1] > 0) {
        int ratio = a[1] / b[1];
        if (equal(b[0] * ratio, a[0]) && equal(b[2] * ratio, a[2])) {
            return ratio;
        }

        return -1;
    }

    if (a[2] > 0) {
        int ratio = a[2] / b[2];
        if (equal(b[0] * ratio, a[0]) && equal(b[1] * ratio, a[1])) {
            return ratio;
        }

        return -1;
    }

    return -1;
}

int main() {
    ifstream fin("ratios.in");
    ofstream fout("ratios.out");
    int a[3], b[3], c[3], res[3];

    fin >> res[0] >> res[1] >> res[2];
    fin >> a[0] >> a[1] >> a[2];
    fin >> b[0] >> b[1] >> b[2];
    fin >> c[0] >> c[1] >> c[2];

    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {
            for (int k = 0; k <= 100; k++) {
                int combo[3];
                int combo_copy[3];
                combo[0] = i*a[0] + j*b[0] + k*c[0];
                combo[1] = i*a[1] + j*b[1] + k*c[1];
                combo[2] = i*a[2] + j*b[2] + k*c[2];

                int ratio = find_ratio(combo, res);
                if (ratio > 0 && ratio <= 100) {
                    fout << i << ' ' << j << ' ' << k << ' ' << ratio << '\n';
                    return 0;
                }
            }
        }
    }

    fout << "NONE\n";
    return 0;
}