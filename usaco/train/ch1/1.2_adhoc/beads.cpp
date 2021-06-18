/*
ID: aaryan.1
TASK: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string> 
#include <vector> 

using namespace std;

int main() {
	ifstream fin ("beads.in");
	ofstream fout ("beads.out");
	
	int n; fin >> n; 
	string neck; fin >> neck; 
	neck = neck + neck;
	
	vector<int> necklaceNum; 
	vector<char> necklaceColor; 
	
	int count = 0;
	for (int i = 0; i < 2 * n; i++) {
		count++;
		if (i != 2 * n - 1) {
			if (neck[i] != neck[i + 1]) {
				necklaceColor.push_back(neck[i]);
				necklaceNum.push_back(count);
				count = 0;
			}
		} else {
			necklaceColor.push_back(neck[i]);
			necklaceNum.push_back(count);
		}
	}
	
	int m = necklaceColor.size();
	int maxCount = -1;
	
	for (int i = 1; i < m; i++) {
		count = 0;
		int type = 0; // r = -1, b = 1
		for (int j = i - 1; j > 0; j--) {
			if (type == 0) {
				if (necklaceColor[j] == 'r') {
					type = -1;
				} else if (necklaceColor[j] == 'b') {
					type = 1;
				}
			} else if (type == -1) {
				if (necklaceColor[j] == 'b') {
					break;
				}
			} else if (type == 1) {
				if (necklaceColor[j] == 'r') {
					break;
				}
			}
			
			count += necklaceNum[j];
		}
		
		type = 0;
		
		for (int j = i; j < m; j++) {
			if (type == 0) {
				if (necklaceColor[j] == 'r') {
					type = -1;
				} else if (necklaceColor[j] == 'b') {
					type = 1;
				}
			} else if (type == -1) {
				if (necklaceColor[j] == 'b') {
					break;
				}
			} else if (type == 1) {
				if (necklaceColor[j] == 'r') {
					break;
				}
			}
			
			count += necklaceNum[j];
		}
		
		//cout << count << endl; 
		if (count > maxCount) {
			maxCount = count;
		}
	}
	
	if (maxCount > neck.size() / 2) {
		fout << neck.size() / 2 << endl;
	} else {
		fout << maxCount << endl;
	}
	
	return 0;
}
