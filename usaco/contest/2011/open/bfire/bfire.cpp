#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
  int n; cin >> n;
  vector<int> nums(n);
  vector<int> moved(n + 1, false);
  
  for (int i = 1; i < n; i++) {
    nums[i] = i + 1;
  }

  int cow = 1;
  int pos = 0;

  while (nums[0] == 0 && !moved[cow]) {
    moved[cow] = true;
    pos += cow;
    pos %= n;

    int temp = cow;
    cow = nums[pos];
    nums[pos] = temp;
  }

  cout << nums[pos] << '\n';

  return 0;
}