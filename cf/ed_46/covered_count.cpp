// :pray: :arceus:
// :pray: :summitosity:
// :pray: :arrayman:

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define ll long long
using namespace std;

typedef struct point point;
struct point {
    ll val;
    bool start;
};

int main() {
    int n; cin >> n;
    vector<point> p;
    
    for (int i = 0; i < n; i++) {
        ll a, b; cin >> a >> b;
        point p1, p2;
        p1.val = a;
        p1.start = true;
        p2.val = b + 1;
        p2.start = false;
        p.push_back(p1);
        p.push_back(p2);
    }
    
    sort(p.begin(), p.end(), [](const point &p1, const point &p2) {
       if (p1.val == p2.val) {
           return p2.start && !p1.start;
       }
       return p1.val < p2.val;
    });
    
    ll level = 0;
    vector<ll> ans(n, 0);
    ll prevNum = 0;
    
    for (int i = 1; i < 2 * n; i++) {
        if (level >= 0) {
            ans[level] += p[i].val - p[i - 1].val;
        }
        
        if (p[i].start) {
            level++;
        } else {
            level--;
        }
    }
    
    for (ll i : ans) {
        cout << i << ' ';
    }
    
    return 0;
}