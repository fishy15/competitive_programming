#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("gradina3.in");
    ofstream fout("gradina3.out");

    int n, k, p; fin >> n >> p >> k;
    vector<vector<bool>> orchard(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        int x, y; fin >> x >> y;
        orchard[x - 1][y - 1] = true;
    }

    for (auto v : orchard) {
        for (auto i : v) {
            cout << i << ' ';
        }

        cout << endl;
    }

    vector<vector<int>> temp1(n, vector<int>(n - k + 1, 0));

    for (int x = 0; x < n; x++) {
        int sum1 = 0;
        for (int j = 0; j < k; j++) {
            sum1 += orchard[x][j];
        }

        temp1[x][0] = sum1;
        for (int i = 1; i < n - k + 1; i++) {
            sum1 += orchard[x][i + k - 1];
            sum1 -= orchard[x][i - 1];
            temp1[x][i] = sum1;
        }
    }

    cout << endl;
    for (auto v : temp1) {
        for (auto i : v) {
            cout << i << ' ';
        }

        cout << endl;
    }

    vector<vector<int>> temp2(n - k + 1, vector<int>(n - k + 1, 0));

    for (int y = 0; y < n - k + 1; y++) {
        int sum1 = 0;
        for (int j = 0; j < k; j++) {
            sum1 += temp1[j][y];
        }

        temp2[0][y] = sum1;
        for (int i = 1; i < n - k + 1; i++) {
            sum1 += temp1[i + k - 1][y];
            sum1 -= temp1[i - 1][y];
            temp2[i][y] = sum1;
        }
    }

    cout << endl;
    for (auto v : temp2) {
        for (auto i : v) {
            cout << i << ' ';
        }

        cout << endl;
    }

    int max = 0;
    int count = 0;
    for (int i = 0; i < n - k + 1; i++) {
        for (int j = 0; j < n - k + 1; j++) {
            if (temp2[i][j] > max) {
                max = temp2[i][j];
            }
        }
    }

    for (int i = 0; i < n - k + 1; i++) {
        for (int j = 0; j < n - k + 1; j++) {
            if(temp2[i][j] == max) {
                count++;
            }
        }
    }

    fout << max << '\n' << count << '\n';
    return 0;
}
