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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n;
string s;
int amt[26];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;
    n = (int)(s.size());

    for (char c : s) {
        amt[c - 'A']++;
    }

    int pos = -1;
    int cnt = 0;
    for (int i = 0; i < 26; i++) {
        if (amt[i] % 2) {
            pos = i;
            cnt++;
        }
    }

    if (cnt > 1) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    for (int i = 0; i < 26; i++) {
        if (i != pos) {
            for (int j = 0; j < amt[i] / 2; j++) {
                cout << (char)('A' + i);
            }
        }
    }

    if (pos >= 0) {
        for (int j = 0; j < amt[pos]; j++) {
            cout << (char)('A' + pos);
        }
    }

    for (int i = 25; i >= 0; i--) {
        if (i != pos) {
            for (int j = 0; j < amt[i] / 2; j++) {
                cout << (char)('A' + i);
            }
        }
    }

    cout << '\n';

    return 0;
}
