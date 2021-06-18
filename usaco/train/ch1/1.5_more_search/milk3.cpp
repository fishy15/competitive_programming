/*
ID: aaryan.1 
TASK: milk3
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <cmath>

#define pii pair<int, int>

using namespace std;

set<int> nums;
set<vector<pii>> visited;
vector<pii> buckets;

void pour(pii &b1, pii &b2);
void unpour(pii &b1, pii &b2, int amt);
int calc(pii b1, pii b2);
void dfs();

int main() {
  ifstream fin("milk3.in");
  ofstream fout("milk3.out");
  
  //cout << "got here\n"; 
  for (int i = 0; i < 3; i++) {
    int x; fin >> x;
    if (i == 2) {
      buckets.push_back({x, x});
    } else {
      buckets.push_back({0, x});
    }
  }
 
  /* 
  for (int i = 0; i < 3; i++) {
    cout << buckets[i].first << " " << buckets[i].second << endl;
  }
  */
  //cout << "got here\n";  
  dfs();
  //cout << "got here\n"; 
  for (auto it = nums.begin(); it != nums.end(); it++) {
    if (it != nums.begin()) {
        fout << " ";
    }

    fout << *it;
  }
  
  fout << "\n";
  
 return 0; 
}

// returns amt poured
void pour(pii &b1, pii &b2, int amt) {
  b1.first -= amt;
  b2.first += amt;
}

// pours back the liquid to reset
void unpour(pii &b1, pii &b2, int amt) {
  b1.first += amt;
  b2.first -= amt;
}

// calcs amt to be poured
int calc(pii b1, pii b2) {
  return min(b1.first, b2.second - b2.first);
}

void dfs() {
  if (visited.find(buckets) == visited.end()) {
    visited.insert(buckets);
    if (buckets[0].first == 0) {
      nums.insert(buckets[2].first);
    }
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        int amt = calc(buckets[i], buckets[j]);
        //cout << buckets[0].first << " " << buckets[1].first << " " << buckets[2].first << endl;
        if (i != j && amt != 0) {
          pour(buckets[i], buckets[j], amt);
          //cout << "pour " << i << " into " << j << endl;
          //cout << "poured " << amt << endl;
          dfs();
          unpour(buckets[i], buckets[j], amt);
        }
      }
    } 
  } /*else {
    cout << buckets[0].first << " " << buckets[1].first << " " << buckets[2].first << endl;
  }*/
}