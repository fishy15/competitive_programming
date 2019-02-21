#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void solve(int n, int c, string s) {
  for (int i = 0; i < c; i++) {
    string sub = s.substr(n, s.size() - n);
    s = sub + s;
  }

  cout << s << '\n';
}

int main() {
  int n; cin >> n;

  for (int i = 0; i < n; i++) {
    int a, b; string s;
    cin >> a >> b >> s;
    solve(a, b, s);
  }
  
  return 0;
}