/*
ID: aaryan.1
TASK: frac1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef struct frac frac;

ofstream fout("frac1.out");

int gcd(int x, int y) {
	if (x > y) {
		return gcd(y, x);
	} else if (x == 0) {
		return y;
	}

	return gcd(x, y % x);
}

struct frac {
	int numerator;
	int denominator;

	frac(int n, int d) {
		numerator = n;
		denominator = d;
	}

	void print() {
		fout << numerator << "/" << denominator << "\n";
	}

	bool simplest() {
		return gcd(numerator, denominator) == 1;
	}
};

int main() {
	ifstream fin("frac1.in");

	int n; fin >> n;

	fout << "0/1\n";
	
	vector<frac> fracs;

	for (int i = n; i > 1; i--) {
		fracs.push_back(frac(1, i));
	}

	while (fracs.size() > 0 && fracs[0].numerator < fracs[0].denominator) {
		fracs[0].print();

		do {
			fracs[0].numerator++;
		} while (!fracs[0].simplest());

		sort(fracs.begin(), fracs.end(), [](const frac &frac1, const frac &frac2) {
			int p1 = frac1.numerator * frac2.denominator;
			int p2 = frac2.numerator * frac1.denominator;

			return p1 < p2;
		});

		/*
		cout << "::::::\n";

		for (int i = 0; i < fracs.size(); i++) {
			fracs[i].print();
		}
		cout << ";;;;;\n";
		*/
	}

	fout << "1/1\n";

	return 0;
}


