#include <iostream>
#include <string>

using namespace std;

int main() {
    string s; cin >> s;
    int start = 0;
    int end = s.size() - 1;
    string ans = "";
    while (end >= start) {
        if ((end - start) % 2 == 1) {
            ans = s[end] + ans;
            end--;
        } else {
            ans = s[start] + ans;
            start++;
        }
    }
    cout << ans << '\n';
    return 0;
}
