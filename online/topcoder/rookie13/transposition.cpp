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

class TranspositionKey {
public:
    vector<int> makeKey(string s) {
        int n = s.size();

        int cnt = 1;
        vector<int> temp(n);
        
        for (char c = 'a'; c <= 'z'; c++) {
            for (int i = 0; i < n; i++) {
                if (s[i] == c || s[i] == c - 'a' + 'A') {
                    temp[i] = cnt;
                    cnt++;
                }
            }
        }

        vector<int> ans;
        for (int x : temp) {
            if (x != 0) {
                ans.push_back(x);
            }
        }

        return ans;
    }
};
