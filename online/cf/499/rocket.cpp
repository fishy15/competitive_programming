#include <iostream>
#include <vector>

using namespace std;

int main() {
    //cin.tie(0); ios::sync_with_stdio(0);

    int m, n; cin >> m >> n;
    vector<bool> works(n, false);

    for (int i = 0; i < n; i++) {
        cout << "1\n";
        fflush(stdout);
        int res; cin >> res;

        if (res == 1) {
            works[i] = true;
        } else if (res == -1) {
            works[i] = false;
        } else {
            return 0;
        }
    }

    int max = 1000000000;
    int min = 1;

    int num = 0;
    while (true) {
        int mid = (min + max) / 2;

        cout << mid << '\n';
        fflush(stdout);
        int res; cin >> res;
        
        if (!works[num]) {
            res *= -1;
        }

        if (res == 1) {
            min = mid + 1;
        } else if (res == -1) {
            max = mid - 1;
        } else {
            return 0;
        }

        num++;
        num %= n;
    }

    return 0;
}
