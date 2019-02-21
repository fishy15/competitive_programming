#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int n;
string s;
int dp[200001][3];
int prev[20001][3];

int main() {
    int n; cin >> n;
    string s; cin >> s;

    if (s[0] == 'R') {
        dp[0][0] = 0;
        dp[0][1] = 1;
        dp[0][2] = 1;
    } else if (s[i] = 'G') {
        dp[0][0] = 1;
        dp[0][1] = 0;
        dp[0][2] = 1;
    } else {
        dp[0][0] = 1;
        dp[0][1] = 1;
        dp[0][2] = 0;
    }

    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == 'R') {
            if (dp[i - 1][1] < dp[i - 1][2]) {
                prev[i - 1][0] = 1;
                
            }
        } else if (s[i - 1] = 'G') {
            dp[0][0] = 1;
            dp[0][1] = 0;
            dp[0][2] = 1;
        } else {
            dp[0][0] = 1;
            dp[0][1] = 1;
            dp[0][2] = 0;
        }
    }
}
