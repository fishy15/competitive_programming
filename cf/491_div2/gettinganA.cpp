#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int roundUp(double n);

int main() {
	int n; cin >> n;
	vector<int> scores;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		scores.push_back(x);
		sum += x;
	}

	int for5 = roundUp(4.5 * n); 
	for5 -= sum;

	sort(scores.begin(), scores.end());

	int index = -1;
	while (for5 > 0) {
		//cout << for5 << endl;
		//cout << index << endl;
		index++;
		for5 -= 5 - scores[index];
	}

	cout << (index + 1) << "\n";

	return 0;
}

int roundUp(double n) {
	if ((int)n == n) {
		return (int)n;
	}

	return (int)(n + 1);
}


		
