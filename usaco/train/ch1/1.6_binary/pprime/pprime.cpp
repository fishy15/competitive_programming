/*
ID: aaryan.1 
TASK: sprime
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void dfs(int prev, int level);
bool prime(int n);

int N;
int options[6] = {1, 2, 3, 5, 7, 9};

ofstream fout("sprime.out");

int main() {
  ifstream fin("sprime.in");
  
  //cout << prime(31) << endl;

  fin >> N;
  dfs(0, 0);
  
  return 0;
}

void dfs(int prev, int level) {
  //cout << "cur: " << prev << endl;
  if (level == N) {
    fout << prev << "\n";
  } else {
    for (int i = 0; i < 6; i++) {
      int next = prev * 10 + options[i];
      if (prime(next)) {
        dfs(next, level + 1);
      }
    }
  }
}

bool prime(int n) {
  if (n == 1) {
    return false;
  }
  
  double sq = sqrt(n);
  for (int i = 2; i <= sq; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  
  return true;
}