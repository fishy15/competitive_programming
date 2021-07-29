#include <iostream>

using namespace std;
typedef long long ll;

int main() {
    int n; cin >> n;

    for (int i = 0; i < n; i++) {
        ll m, k; cin >> m >> k;
        ll total = 0;
        ll pow = 1;
        ll counter = 0;

        while (total < k && counter < m) {
            total += pow;
            counter += 1;
            pow *= 4;
            //cout << total << " at " << counter << endl;
        }
        
        if (total >= k) {
            cout << "YES " << m - counter << '\n';
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
