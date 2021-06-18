/*
ID: aaryan.1
TASK: transform
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// all these rotations are counter-clockwise
// problem needs them to be clockwise
vector<string> rotate90(vector<string> original);
vector<string> rotate180(vector<string> original);
vector<string> rotate270(vector<string> original);
vector<string> reflect(vector<string> original);

int main() {
	ifstream fin("transform.in");
	ofstream fout("transform.out");

	int row; fin >> row;
	vector<string> original(row, "");

	for(int i = 0; i < row; i++) {
		string rowVal; fin >> rowVal;
		original[i] = rowVal;
	}

	vector<string> newer(row, "");

	for (int i = 0; i < row; i++) {
		string rowVal; fin >> rowVal;
		newer[i] = rowVal;
	}

	if (rotate270(original) == newer) {
		fout << "1\n";
	} else if (rotate180(original) == newer) {
		fout << "2\n";
	} else if (rotate90(original) == newer) {
		fout << "3\n";
	} else if (reflect(original) == newer) {
		fout << "4\n";
	} else if (rotate90(reflect(original)) == newer|| rotate180(reflect(original)) == newer || rotate270(reflect(original)) == newer ) {
		fout << "5\n";
	} else if (original == newer) {
		fout << "6\n";
	} else {
		fout << "7\n";
	}

	return 0;
}

/* conv 
1 2 3
4 5 6
7 8 9
to
3 6 9
2 5 8
1 4 7
*/

vector<string> rotate90(vector<string> original) {
	int rows = original.size();
	vector<string> ans(rows, "");
	for (int i = 0; i < rows; i++) {
		string rowVal = "";
		for (int j = 0; j < rows; j++) {
			rowVal += original[j][rows - i - 1];
		}

		ans[i] = rowVal;
	}

	return ans;
}

/* conv 
1 2 3
4 5 6
7 8 9
to
9 8 7
6 5 4
3 2 1
*/
vector<string> rotate180(vector<string> original) {
	int rows = original.size();
	vector<string> ans(rows, "");
	for (int i = 0; i < rows; i++) {
		string rowVal = "";
		for (int j = 0; j < rows; j++) {
			rowVal += original[rows - i - 1][rows - j - 1];
		}

		ans[i] = rowVal;
	}

	return ans;
}

/* conv 
1 2 3
4 5 6
7 8 9
to
7 4 1
8 5 2
9 6 3
*/
vector<string> rotate270(vector<string> original) {
	int rows = original.size();
	vector<string> ans(rows, "");
	for (int i = 0; i < rows; i++) {
		string rowVal = "";
		for (int j = 0; j < rows; j++) {
			rowVal += original[rows - j - 1][i];
		}

		ans[i] = rowVal;
	}

	return ans;
}

/* conv
1 2 3
4 5 6
7 8 9
to
7 8 9
4 5 6
1 2 3
*/
vector<string> reflect(vector<string> original) {
	int rows = original.size();
	vector<string> ans(rows, "");
	for (int i = 0; i < rows; i++) {
		string rowVal = "";
		for (int j = 0; j < rows; j++) {
			rowVal += original[i][rows - j - 1];
		}

		ans[i] = rowVal;
	}

	return ans;
}


