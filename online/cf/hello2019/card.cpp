#include <iostream>
#include <string>

using namespace std;

int main() {
    string down; 
    string hand[5];

    cin >> down;
    for (int i = 0; i < 5; i++) {
        cin >> hand[i];
    }

    for (int i = 0; i < 5; i++) {
        if (down[0] == hand[i][0]) {
            cout << "YES\n";
            return 0;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (down[1] == hand[i][1]) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";
    return 0;
}
