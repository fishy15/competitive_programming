/*
ID: aaryan.1
TASK: fence9
LANG: C++11
*/

// :pray: :fishy:

#include <iostream>
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

int gcd(int x, int y) {
    if (x > y) {
        return gcd(y, x);
    }

    if (x == 0) {
        return y;
    }

    return gcd(y % x, x);
}

int main() {
    ifstream fin("fence9.in");
    ofstream fout("fence9.out");

    int n, m, p; fin >> n >> m >> p;
    int i = gcd(m, n) + gcd(abs(n - p), m) + p;
    cout << i << '\n';
    int area = m * p;
    fout << (area - i + 2) / 2 << '\n';

    return 0;
}
