#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	ifstream fin("crescator.in");
	ofstream fout("crescator.out");

	int n; fin >> n;
	vector<int> nums(n);

	for (int i = 0; i < n; i++) {
		fin >> nums[i];
	}

    vector<int> len(n);
    len[n - 1] = 1;

    for (int i = n - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) {
            len[i] = len[i + 1] + 1;
        } else {
            len[i] = 1;
        }
    }

    int count = 0;
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        maxLen = len[i] > maxLen ? len[i] : maxLen;
        count += len[i];
    }

	fout << count << ' ' << maxLen << '\n';
	return 0;
}
