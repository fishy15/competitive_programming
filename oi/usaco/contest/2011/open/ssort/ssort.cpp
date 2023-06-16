#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int sum;

void sort(vector<int> &nums) {
  if (nums.size() == 0) return;

  int half = (int)(nums.size()) / 2;
  
  vector<int> part1;
  vector<int> part2;
  
  for (int i = 0; i < half; i++) {
    part1.push_back(nums[i]);
    part2.push_back(nums[i + half]);
  }

  sort(part1);
  sort(part2);

  if (part1 < part2) {
    for (int i = 0; i < half; i++) {
      nums[i] = part1[i];
      nums[i + half] = part2[i];
    } 
  } else {
    for (int i = 0; i < half; i++) {
      nums[i] = part2[i];
      nums[i + half] = part1[i];
      sum += nums.size();
    }
  }
}

int main() {
  int n; cin >> n;
  vector<int> nums((1 << n));
  
  for (int i = 0; i < nums.size(); i++) {
    cin >> nums[i];
  }

  sort(nums);

  cout << sum << '\n';
  for (int i : nums) {
    cout << i << '\n';
  }

  return 0;
}