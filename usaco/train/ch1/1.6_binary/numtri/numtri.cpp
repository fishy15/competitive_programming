/*
ID: aaryan.1 
TASK: numtri
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#define vi vector<int>

using namespace std;

int n;
vector<vi> triangle;
vi back_track(int layer);

int main() {
  ifstream fin("numtri.in");
  ofstream fout("numtri.out");
  
  fin >> n;
  
  for (int i = 1; i <= n; i++) {
    vector<int> layer;
    for (int j = 0; j < i; j++) {
      int x; fin >> x;
      layer.push_back(x);
    }
    
    triangle.push_back(layer);
  }
  
  vi ans = back_track(0);
  fout << ans[0] << "\n";
  
  return 0;
}

vi back_track(int layer) {
  if (layer == n - 1) {
    return triangle[n-1];
  } else {
    vi ans(layer + 1);
    vi next = back_track(layer + 1);
    for (int i = 0; i <= layer; i++) {
      ans[i] = max(next[i], next[i + 1]) + triangle[layer][i];
      //cout << ans[i] << " ";
    }
    
    //cout << "\n";
    
    return ans;
  }
}    