#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() { 
	int n, k; cin >> n >> k;
	vector<int> bac;

	for (int i = 0; i < n; i++) {
		int b; cin >> b;
		bac.push_back(b);
	}

	sort(bac.begin(), bac.end());

	int repLen = 0;
	int prevRepLen = 0;
	for (int i = 1; i < bac.size(); i++) {
		//cout << "!" << bac[i] << endl;
		
		//cout << "R" << repLen << "P" << prevRepLen << endl;
		if (bac[i] == bac[i - 1]) {
			//cout << "rep\n";
			 repLen++;
			 continue;
		}

		prevRepLen = repLen;
		repLen = 0;

		if (bac[i - 1] + k >=  bac[i]) {
			//cout << "del\n";
			for (int j = i - prevRepLen - 1; j < i; j++) {
				//cout << j << endl;
				bac[j] = -1;
			}
		}

	}

	int count = 0;
	for (int i = 0; i < bac.size(); i++) {
		  //cout << bac[i] << endl;
		if (bac[i] != -1) {
			count++;
		}
	}

	cout << count << endl;

	return 0;
}
