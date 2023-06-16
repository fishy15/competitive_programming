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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

class Scramble {
public:
    string scrambleWord(string word) {
        int n = word.length();

        string first = word.substr(0, 1);
        string last = word.substr(n - 1, 1);

        string mid = word.substr(1, n - 2);
        sort(mid.begin(), mid.end());

        int cnt = 0;
        for (char c : mid) {
            if (cnt % 2 == 0) first += c;
            else last += c;
            cnt++;
        }

        reverse(last.begin(), last.end());
        return first + last;
    }
};
