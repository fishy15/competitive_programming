#include <iostream>
#include <vector>

#define abs(x) (x) > 0 ? (x) : -(x)

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int p; cin >> p;
    double m; cin >> m;
    double f = 1.0;

    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < p; i++) {
            double x; cin >> x;

            if (x == 1) {
                cout << "-1\n";
                return 0;
            }

            f *= x - 1;
            f /= x;
            //cout << f << endl;
        }
    }

    cout << m * (1 - f) / f << '\n';

    return 0;
}
