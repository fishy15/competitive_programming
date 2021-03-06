#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    vector<int> coord;

    for (int i = 0; i < 2*n; i++) {
        int x; cin >> x;
        coord.push_back(x);
    }

    sort(coord.begin(), coord.end());

    /*
    for (int i : coord) {
        cout << i << ' ';
    } cout << '\n';
    */
   
    //cout << coord[n - 1] - coord[0] << '\n';
    //cout << coord[2*n - 1] - coord[n] << '\n';
    int min = (coord[n - 1] - coord[0]) * (coord[2*n - 1] - coord[n]);
    cout << "init: " << min << '\n';
    for (int i = 1; i < n; i++) {
        cout << (i + n - 1) << ' ' << i << ' ';
        int res = (coord[2*n - 1] - coord[0]) * (coord[i + n - 1] - coord[i]);
        //cout << i << ' ' << res << '\n';
        min = res < min ? res : min;
        cout << res << '\n';
    }

    cout << min << '\n';

    return 0;
}
