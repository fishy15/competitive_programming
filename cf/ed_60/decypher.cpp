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
vector<int> perm;
vector<int> rev;

int main() {
    cin >> s;
    n = (int)(s.size());
    perm.resize(n);
    rev.resize(n);

    string q = "";
    for (int i = 0; i < n; i++) {
        q.push_back((char)('a' + (i % 26)));
    }
    cout << "? " << q << endl;
    string res; cin >> res;
    for (int i = 0; i < n; i++) {
        perm[i] += res[i] - 'a';
    }

    q = "";
    for (int i = 0; i < n; i++) {
        q.push_back((char)('a' + (i / 26 % 26)));
    }
    cout << "? " << q << endl;
    cin >> res;
    for (int i = 0; i < n; i++) {
        perm[i] += 26 * (res[i] - 'a');
    }

    q = "";
    for (int i = 0; i < n; i++) {
        q.push_back((char)('a' + (i / 26 / 26)));
    }
    cout << "? " << q << endl;
    cin >> res;
    for (int i = 0; i < n; i++) {
        perm[i] += 26 * 26 * (res[i] - 'a');
    }

    for (int i = 0; i < n; i++) {
        rev[perm[i]] = i;
    }

    cout << "! ";
    for (int i = 0; i < n; i++) {
        cout << s[rev[i]];
    } cout << endl;

    return 0;
}
