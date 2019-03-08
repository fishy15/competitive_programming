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
// :pray: :horse:
// :pray: :snek:
// :pray: :wayne:
// :pray: :wu:

#include <iostream>
#include <algorithm>
#include <vector>

#define eps 1e-8

using namespace std;

struct frac {
    int num;
    int denom;

    frac(int num, int denom) {
        int gcd = __gcd(num, denom);
        this->num = num / gcd;
        this->denom = denom / gcd;
    }

    bool operator<(const frac &f) const {
        return num * f.denom < f.num * denom;
    }

    bool operator==(const frac &f) const {
        return num * f.denom == f.num * denom;
    }
};

int n;
int a[200001];
int b[200001];
vector<pair<frac, int>> vals;

int main() {
    cin >> n;;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    int zero = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] != 0) {
            vals.push_back({frac(b[i], a[i]), i});
        } else if (b[i] == 0){
            zero++;
        }
    }
    
    sort(vals.begin(), vals.end());
    
    int l = 0;
    int r = 0;
    int cur = 0;
    int ans = 0;
    
    while (l < vals.size()) {
        //cout << vals[l].first.num << " / " << vals[l].first.denom << '\n';
        while (r < vals.size() && vals[r].first == vals[l].first) {
            if (a[vals[r].second] != 0) cur++;
            r++;
        }
        
        ans = cur > ans ? cur : ans;
        //cout << l << ' ' << r << '\n';
        l++;
        cur = 0;
    }

    cout << ans + zero << '\n';
}