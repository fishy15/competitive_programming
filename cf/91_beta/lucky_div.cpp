#include <iostream>
#include <vector>

using namespace std;

vector<int> check = {4,7,44,47,74,77,444,447,474,477,744,747,774,777};

int main() {
    cin.tie(0); ios::sync_with_stdio(0);
    int n; cin >> n;

    for (int i = 0; i < check.size(); i++) {
        if (n % check[i] == 0) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";
    return 0;
}
