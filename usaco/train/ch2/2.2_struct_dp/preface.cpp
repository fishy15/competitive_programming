/*
ID: aaryan.1
TASK: preface
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int ans[7];
char let[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

int main() {
	ifstream fin("preface.in");
	ofstream fout("preface.out");

	int n; fin >> n;

	for (int i = 1; i <= n; i++) {
		int num = i;
		int ones = num % 10;
		if (ones % 5 == 4) {
			ans[0]++;
		} else {
			ans[0] += ones % 5;
		}

		if (ones >= 4 && ones < 9) {
			ans[1]++;
		} else if (ones == 9) {
			ans[2]++;
		}

		num /= 10;
		int tens = num % 10;

		if (tens % 5 == 4) {
			ans[2]++;
		} else {
			ans[2] += tens % 5;
		}

		if (tens >= 4 && tens < 9) {
			ans[3]++;
		} else if (tens == 9) {
			ans[4]++;
		}

		num /= 10;
		int huns = num % 10;
		if (huns % 5 == 4) {
			ans[4]++;
		} else {
			ans[4] += huns % 5;
		}

		if (huns >= 4 && huns < 9) {
			ans[5]++;
		} else if (huns == 9) {
			ans[6]++;
		}

		num /= 10;
		int thos = num % 10;

		if (thos % 5 == 4) {
			ans[6]++;
		} else {
			ans[6] += thos % 5;
		}
	}

	int index = 0;
	while (index < 7 && ans[index] > 0) {
		fout << let[index] << ' ' << ans[index] << '\n';
		index++;
	}

	return 0;
}
