#include <iostream>
#include <vector>

typedef long long ll;

using namespace std;

int main() {
    int n, k; ll s; cin >> s;
    vector<int> moves(k , 1);

    for (int i = 0; i < k; i += 2) {
        moves[i] = 2;
    }

    ll dist = k;
    if (k > s) {
        cout << "NO\n";
        return 0;
    }

    // ends in 1, go down to sol
    if (k % 2 == 0) {
        for (int i = 0; i < k; i += 2) {
            moves[i] = n;
            dist += 2*(n - 2);
        }

        int index = k - 2;
    }
}
