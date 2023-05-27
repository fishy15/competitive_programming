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

int n;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    string s;
    getline(cin, s); // feed \n
    for (int i = 0; i < n; i++) {
        string s; 
        getline(cin, s);
        if (s.size() >= 10 && s.substr(0, 10) == "Simon says") {
            cout << s.substr(11, s.size() - 10) << '\n';
        }
    }

    return 0;
}
