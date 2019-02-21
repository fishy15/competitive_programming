#include <iostream>
#include <vector>

#define min(a, b) (a) > (b) ? (b) : (a)
typedef long long ll;

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n, k; ll s; cin >> n >> k >> s;
    vector<int> moves(k, 1);

    for (int i = 0; i < k; i++) {
        if (i % 2 == 0) {
            moves[i] = 2;
        }
    }

    ll dist = k;
    if (dist > s || (n-1)*k < s) {
        cout << "NO\n";
        return 0;
    }

    for (int i = 0; i < k; i += 2) {
        if (k % 2 == 1 && dist > s - (2 * (n - 2))) {
            break;
        }

        moves[i] = n;
        dist += 2 * (n - 2);
        if (k % 2 == 0 && i == k - 1) {
            dist -= n - 2;
        }

        if (k % 2 == 0 && dist > s) {
            break;
        }
    }

    /*
    for (int i = 0; i < k; i++) {
        cout << moves[i] << ' ';
    }
    cout << endl;
    cout << dist << '\n';
    */

    if (k % 2 == 0) {
        int res = min(1 + dist - s, n);
        moves[k - 1] = res;
        if (k > 2) {
            moves[k - 3] -= (dist - s + 1 - res) / 2;
        }
        if (moves[k - 1] > n || moves[k - 1] <= 0) {
            cout << "NO\n";
            return 0;
        }
    } else {
        moves[k - 1] -= dist - s;
        if (moves[k - 1] > n || moves[k - 1] <= 0) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";

    for (int i = 0; i < k; i++) {
        cout << moves[i] << ' ';
    }

    cout << '\n';
    return 0;
}
