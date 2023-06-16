#include <iostream>
#include <string>
#include <vector>
#include <queue>

#define ll long long

using namespace std;

int main() {
    ll u, p, c; cin >> u >> p >> c;
    ll m; cin >> m;
    priority_queue<ll, vector<ll>, greater<ll>> usb;
    priority_queue<ll, vector<ll>, greater<ll>> ps2;
    
    for (ll i = 0; i < m; i++) {
        ll c; string t; 
        cin >> c >> t;
        if (t == "USB") {
            usb.push(c);
        } else {
            ps2.push(c);
        }
    }
    
    ll count = 0;
    ll cost = 0;
    
    for (ll i = 0; i < u; i++) {
        if (usb.empty()) {
            break;
        }
        
        count++;
        cost += usb.top();
        usb.pop();
    }
    
    for (ll i = 0; i < p; i++) {
        if (ps2.empty()) {
            break;
        }
        
        count++;
        cost += ps2.top();
        ps2.pop();
    }
    
    priority_queue<ll, vector<ll>, greater<ll>> combo;
    
    while (!ps2.empty()) {
        combo.push(ps2.top());
        ps2.pop();
    }
    
    while (!usb.empty()) {
        combo.push(usb.top());
        usb.pop();
    }
    
    for (ll i = 0; i < c; i++) {
        if (combo.empty()) {
            break;
        }
        
        count++;
        cost += combo.top();
        combo.pop();
    }
    
    cout << count << ' ' << cost << '\n';
}