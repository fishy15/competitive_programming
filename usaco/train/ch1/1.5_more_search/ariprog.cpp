/*
ID: aaryan.1
TASK: ariprog
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
  ifstream fin("ariprog.in");
  ofstream fout("ariprog.out");
  int n, m; fin >> n >> m;
  cout << "m = " << m << endl;
  int sz = 2*m*m+1;
  set<int> bisq;  
  vector<bool> bisqb(sz);
  vector<pair<int, int>> ans;

  for (int i = 0; i <= m; i++) {
    for (int j = i; j <= m; j++) {
      int x = i*i + j*j;
      bisqb[x] = true;
    }
  }
  
  for (int a = 0; a < sz; a++) {
    for (int b = 1; b <= (sz - a) / (n - 1); b++) {
      int f;
      for (f = 0; f < n; f++) {
        if (a + f*b >= sz || !bisqb[a + f*b]) {
          break;
        }
      }

      if (f == n) {
        ans.push_back({b, a});
        cout << "found 1\n";
      }
    }
  }
  
  sort(ans.begin(), ans.end());
  
  if (ans.empty()) {
    fout << "NONE\n";
  } else {
    for (pair<int, int> p : ans) {
      fout << p.second << " " << p.first << "\n"; 
    }
  }

  /*
  for (int b = 1; b < sz / m; b++) {
    for (int a = 0; a < sz; a++) {
      int f;
      for (f = 0; f < n; f++) {
        if (a + f*b >= sz || !bisqb[a + f*b]) {
          break;
        }
      }

      if (f == n) {
        cout << a << " " << b << "\n";
      }
    }
  }
  */
  
  return 0;
}