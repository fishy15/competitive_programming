/*
ID: aaryan.1
TASK: game1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n;
vector<int> nums;
// max you can get from range i to j - 1
int dp[201][201];

int prefix[201];

int calcRange(int l, int r) {
    return prefix[r] - prefix[l];
}

int main() {
    ifstream fin("game1.in");
    ofstream fout("game1.out");

    fin >> n;

    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        nums.push_back(x);
        prefix[i + 1] = prefix[i] + x;
    }

    for (int diff = 1; diff <= n; diff++) {
        for (int l = 0; l < n; l++) {
            int r = l + diff;
            if (r > n) break;

            if (dp[l][r - 1] > dp[l + 1][r]) {
                dp[l][r] = calcRange(l, r) - dp[l + 1][r];
            } else {
                dp[l][r] = calcRange(l, r) - dp[l][r - 1];
            }
        }
    }

    /*
    for (int l = 0; l < n; l++) {
        for (int r = 1; r <= n; r++)
            cout << l << ' ' << r << ' ' << dp[l][r] << endl;
    }
    */
    

    fout << dp[0][n] << ' ' << prefix[n] - dp[0][n] << '\n';
}