#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int n;
char space[101][101][101];

void floodfill(int i, int j, int k) {
  space[i][j][k] = '.';

  if (i > 0 && space[i - 1][j][k] == '*') {
    floodfill(i - 1, j, k);
  }

  if (j > 0 && space[i][j - 1][k] == '*') {
    floodfill(i, j - 1, k);
  }

  if (k > 0 && space[i][j][k - 1] == '*') {
    floodfill(i, j, k - 1);
  }

  if (i < n - 1 && space[i + 1][j][k] == '*') {
    floodfill(i + 1, j, k);
  }
  
  if (j < n - 1 && space[i][j + 1][k] == '*') {
    floodfill(i, j + 1, k);
  }

  if (k < n - 1 && space[i][j][k + 1] == '*') {
    floodfill(i, j, k + 1);
  }
}

int main() {
  cin >> n;

  getchar();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        space[i][j][k] = getchar();
      }

      getchar();
    }
  }

  /*
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        cout << space[i][j][k];
      }
      cout << endl;
    }
  }
  */

  int count = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        if (space[i][j][k] == '*') {
          count++;
          floodfill(i, j, k);
        }
      }
    }
  }

  cout << count << '\n';

  return 0;
}