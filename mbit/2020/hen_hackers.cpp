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

vector<char> cur;

void proc(char c) {
    char res;
    cout << c << '\n';
    cout.flush();
    cin >> res;

    if (res == 'N') return;
    int l = 0;
    int r = cur.size();
    int ans = -1;

    while (l <= r) {
        int m = (l + r) / 2;
        for (int i = 0; i < m; i++) {
            cout << cur[i];
        }
        cout << c << '\n';
        cout.flush();
        cin >> res;

        if (res == 'N') {
            r = m - 1;
        } else {
            l = m + 1; 
            ans = m;
        }
    }

    cur.insert(cur.begin() + ans, c);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i = 'A'; i <= 'Z'; i++) proc(i);
    for (int i = 'a'; i <= 'z'; i++) proc(i);
    for (int i = '0'; i <= '9'; i++) proc(i);

    for (char c : cur) {
        cout << c;
    }
    
    cout << '\n';
    cout.flush();

    char res; cin >> res;

    return 0;
}
