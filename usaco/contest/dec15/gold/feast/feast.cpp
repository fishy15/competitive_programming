#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("feast.in");
    ofstream fout("feast.out");

    int t, a, b; fin >> t >> a >> b;
    vector<bool> works(t + 1, 0);
    works[0] = true;

    for (int i = 1; i <= t; i++) {
        if (i - a >= 0 && works[i - a]) {
            works[i] = true;
        } else if (i - b >= 0 && works[i - b]) {
            works[i] = true;
        }
    }

    for (int i = 0; i <= t; i++) {
        if (works[i]) {
            works[i/2] = true;
        }
    }

    for (int i = 1; i <= t; i++) {
        if (i - a >= 0 && works[i - a]) {
            works[i] = true;
        } else if (i - b >= 0 && works[i - b]) {
            works[i] = true;
        }
    }

    int ans = t;
    for (; ans >= 0; ans--) {
        if (works[ans]) break;
    }

    fout << ans << '\n';
    return 0;
}