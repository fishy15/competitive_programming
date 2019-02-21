/*
ID: aaryan.1
TASK: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct range {
	int begin, end; 
	
	range (int beginIn, int endIn) {
		begin = beginIn;
		end = endIn; 
	}
	
	bool inside(int pos) {
		return (pos >= begin) && (pos < end);
	}
	
	int size() {
		return end - begin;
	} 
};

int main() {
	ifstream fin ("milk2.in");
	ofstream fout ("milk2.out");
	
	int n; fin >> n; 
	int max = 0;
	int min = 5000;
	vector<range> checker;
	
	for (int i = 0; i < n; i++) {
		int a, b;
		fin >> a >> b;
		checker.push_back(range(a, b)); 
		if (b > max) {
			max = b;
		}
		if (a < min) {
			min = a;
		}
	}
	
	vector<bool> points(max, false);

	for (int  i = min; i < max; i++) {
		for (int j = 0; j < checker.size(); j++) {
			if (checker[j].inside(i)) {
				for (int k = i; k < checker[j].end; k++) {
					points[k] = true;
				}
				i = checker[j].end - 1;
				break;
			}
		}
	}
	 
	int maxT = 0;
	for (int i = min; i < points.size(); i++) {
		int len = 0;
		while (points[i] && i < points.size()) {
			len++;
			i++;
		}
		
		if (len > maxT) {
			maxT = len;
		}
	}

	int maxF = 0;
	for (int i = min; i < points.size(); i++) {
		int len = 0;
		while (points[i] == 0 && i < points.size()) {
			len++;
			i++;
		}
		
		if (len > maxF) {
			maxF = len;
		}
	}


	fout << maxT << " " << maxF << endl;

	return 0; 
}
