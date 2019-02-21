#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int points[500][2];
int dp[500][500];

int main() {
    ifstream fin("marathon.in");
    ofstream fout("marathon.out");

    int n, k; fin >> n >> k;

    for (int i = 0; i < n; i++) {
        fin >> points[i][0] >> points[i][0];
    }

    // set up dp
    int curDist = 0;
    for (int i = 1; i < n; i++) {
        curDist += abs(points[i][0] - points[i - 1][0]) + abs(points[i][1] - points[i - 1][0]);
        dp[i][0] = curDist;
    }

    for (int skip = 1; skip <= k; skip++) {
        for (int j = 2; j < n; j++) {
            int distPrev = abs(points[j][0] - points[j - 2][0]) + abs(points[j][1] - points[j - 2][0]);
            int distPrev2 = abs(points[j][0] - points[j - 1][0]) + abs(points[j][1] - points[j - 1][0]);
            dp[j][skip] = min(dp[j - 1][skip] + distPrev2, dp[j - 2][skip - 1] + distPrev);
        }
    }

    cout << dp[n - 1][k] << '\n';
    return 0;
}