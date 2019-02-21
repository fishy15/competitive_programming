#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("planting.in");
    ofstream fout("planting.out");

    int n; fin >> n;
    vector<vector<int>> connect(n);

    for (int i = 0; i < n - 1; i++) {
        int x, y; fin >> x >> y;
        x--; y--;
        //cout << "P: " << x << ' ' << y << endl;
        connect[x].push_back(y);
        connect[y].push_back(x);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int val = connect[i].size();
        //cout << val << endl;
        for (int j : connect[i]) {
            //cout << j << ' ';
            if (connect[j].size() > val) {
                val = connect[j].size();
            }
        } //cout << endl;

        if (val > ans) {
            ans = val;
        }

        //cout << i << ' ' << val << endl;
    }

    fout << ans + 1 << '\n';
    return 0;
}