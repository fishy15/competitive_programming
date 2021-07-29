#include <iostream>
#include <queue>

#define ll long long

using namespace std;

int main() {
    int n; cin >> n;
    priority_queue<int> a, b;
    
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a.push(x);
    }
    
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        b.push(x);
    }
    
    ll diff = 0;
    
    for (int i = 0; i < n; i++) {
        // person A turn
        if (a.empty()) {
            b.pop();
        } else if (b.empty()) {
            diff += a.top();
            a.pop();
        } else {
            if (a.top() > b.top()) {
                diff += a.top();
                a.pop(); 
            } else {
                b.pop();
            }
        }
        
        // person B turn
        if (a.empty()) {
            diff -= b.top();
            b.pop();
        } else if (b.empty()) {
            a.pop();
        } else {
            if (b.top() > a.top()) {
                diff -= b.top();
                b.pop(); 
            } else {
                a.pop();
            }
        }
    }
    
    cout << diff << '\n';
}