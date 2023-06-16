#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int k;

string pre1[4] = {"", "1", "01", "001"};
string seg1 = "1001";
int ans1[4] = {0, 1, 1, 0};

string pre2[8] = {
    "",
    "0",
    "01",
    "001",
    "0001",
    "10001",
    "010110",
    "1101001",
};
string seg2 = "01101001";
int ans2[8] = {0, 1, 3, 4, 2, 3, 1, 0};

string pre3[16] = {
    "",
    "0",
    "01",
    "001",
    "0001",
    "00001",
    "100001",
    "0001110",
    "11001001",
    "011010110",
    "0000000101",
    "11110010110",
    "110100011001",
    "1100001010110",
    "01011001101001",
    "110000101000011",
};
string seg3 = "1001011001101001";
int ans3[16] = {0, 1, 7, 18, 28, 25, 7, 26, 4, 5, 1, 12, 0, 1, 1, 0};

string pre4[32] = {
    "",
    "0",
    "01",
    "001",
    "0001",
    "00001",
    "000001",
    "0000001",
    "00101110",
    "000001110",
    "0101001001",
    "00000101001",
    "110010101001",
    "1101001010110",
    "00000001111010",
    "011110001010110",
    "0000111000001110",
    "00101000011111100",
    "000000110100001110",
    "1101001001011110001",
    "00110000001011011010",
    "000000000100100100011",
    "0000110000011011101010",
    "10111000000000100110110",
    "001010000000001100111010",
    "0101000000001110101110001",
    "00010100000100010000110101",
    "011010000000001010000110101",
    "1010110000000000101101100110",
    "00010000000100110001000101110",
    "101100000000000100111000111010",
    "1110000000000000001010110010101"
};
string seg4 = "01101000000000001011100010111100";
int ans4[32] = {0, 1, 15, 64, 158, 271, 317, 126, 34, 253, 13, 92, 30, 47, 31, 2, 0, 1, 13, 0, 0, 9, 1, 0, 0, 1, 5, 0, 0, 5, 1, 0};

void solve() {
    int n; cin >> n;
    if (k == 1) {
        cout << ans1[n % 4] << '\n';
        cout << pre1[n % 4];
        for (int i = 0; i < n / 4; i++) cout << seg1;
        cout << '\n';
    } else if (k == 2) {
        cout << ans2[n % 8] << '\n';
        cout << pre2[n % 8];
        for (int i = 0; i < n / 8; i++) cout << seg2;
        cout << '\n';
    } else if (k == 3) {
        cout << ans3[n % 16] << '\n';
        cout << pre3[n % 16];
        for (int i = 0; i < n / 16; i++) cout << seg3;
        cout << '\n';
    } else {
        cout << ans4[n % 32] << '\n';
        cout << pre4[n % 32];
        for (int i = 0; i < n / 32; i++) cout << seg4;
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> k;
    int t; cin >> t;
    while (t--) solve();

    return 0;
}
