/*
ID: aaryan.1
TASK: milk
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct farmer farmer;

struct farmer {
	int price, number; 

	farmer(int p, int num) {
		number = num;
		price = p;
	}
};

int main() {
	ifstream fin("milk.in");
	ofstream fout("milk.out");

	int n, m; fin >> m >> n;
	vector<farmer> farmers;

	for (int i = 0; i < n; i++) { 
		int a, b; fin >> a >> b;
		farmers.push_back(farmer(a, b));
	}

	sort(farmers.begin(), farmers.end(), [] (farmer a, farmer b) {
		return a.price < b.price;
	});

	int ans = 0;
	int counter = 0;
	while (m > 0) {
		//cout << farmers[counter].price << endl;
		if (farmers[counter].number >= m) {
			ans += m * farmers[counter].price;
			break;
		}

		ans += farmers[counter].price * farmers[counter].number;
		m -= farmers[counter].number;
		counter++;
	}

	fout << ans << endl;

	return 0;
}

	
