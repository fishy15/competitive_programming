#include <iostream>
#include <string> 
#include <vector>

using namespace std; 

int main() {
    int n, k; cin >> n >> k; 
    int count = 0;
    int p = 0; 
    vector<int> scores; 
    for (int i = 0; i < n; i++) {
        int x; cin >> x; 
        if (x == 0 || x < p) {
            break; 
        } else if (i == k - 1) {
            p = x; 
        }
        count++;
    }
    cout << count << endl;
}
