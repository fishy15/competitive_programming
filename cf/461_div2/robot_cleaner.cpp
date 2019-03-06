// :pray: :arrayman:
// :pray: :summitosity:
// :pray: :pusheenosity:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk-duk-go:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eediosity:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinxiosity
// :pray: :eggyosity:
// :pray: :squares-are-fine:
// :pray: :see-jay:
// :pray: :stephiosity:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:m

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define ll long long 

using namespace std;

ll calcVal(string s) {
    ll hCount = 0;
    ll ans = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == 'h') {
            hCount++;
        } else {
            ans += hCount;
        }
    }
    
    //cout << s << ' ' << ans << endl;
    return ans;
}

typedef struct str str;
struct str {
    string s;
    ll val;
    ll sCount = 0;
    ll hCount = 0;
    double ratio;
    
    str(string s2) {
        s = s2;        
        for (char c : s2) {
            if (c == 's') {
                sCount++;
            } else {
                hCount++;
            }
        }
        
        if (hCount == 0) {
            ratio = 100001;
        } else {
            ratio = 1.0 * sCount / hCount;
        }
    }
};

bool cmp(str &s1, str &s2) {
    return s1.ratio > s2.ratio;
}

int main() {
    int n; cin >> n;
    vector<str> strs;
    
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        strs.push_back(str(s));
    }
    
    sort(strs.begin(), strs.end(), cmp);
    
    string res = "";
    for (int i = 0; i < n; i++) {
        res += strs[i].s;
    }
    
    //cout << res << '\n';
    cout << calcVal(res) << '\n';
}