#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

typedef long long ll;

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n, m; cin >> n >> m;
    // normal, compressed
    vector<int> changes;
    ll size = 0;

    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        changes.push_back(x - y);
        size += y;
    }

    if (size > m) {
        cout << "-1\n";
        return 0;
    }

    sort(changes.begin(), changes.end());

    /*
    for (int i : changes) {
        cout << i << ' ';
    }
    cout << endl;
    */

    int i = 0;
    for (i = 0; i < n; i++) {
        //cout << size << '\n';
        if (size + changes[i] > m) {
            break;
        }

        size += changes[i];
    }

    cout << n - i << '\n';
    return 0;
}
