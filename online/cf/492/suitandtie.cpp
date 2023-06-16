#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

typedef struct person person;

struct person {
	int pos;
	person *partner;
	bool paired = false;

	person(int posi) {
		pos = posi;
	}

	void set(person p) {
		partner = &p;
	}

	int dist() {
		return this->pos - partner->pos;
	}
};

void backswap(vector<person> &ppl, int initial, int end) {
	person temp = ppl[initial];
	for (int i = initial - 1; i >= end; i--) {
		ppl[i].pos++;
		ppl[i] = ppl[i + 1];
	}

	ppl[end] = temp;
}

void frontswap(vector<person> &ppl, int initial, int end) {
	person temp = ppl[initial];
	for (int i = initial + 1; i <= end; i++) {
		ppl[i].pos--;
		ppl[i - 1] = ppl[i];
	}

	ppl[end] = temp;
}

int main() {
	int n; cin >> n;
	vector<int> ppl;
	for (int i = 0; i < 2*n; i++) {
		int x; cin >> x;
		ppl.push_back(x);
	}

	vector<person> ppls(2*n, -1);

	for (int i = 0; i < 2*n - 1; i++) {
		for (int j = i + 1; j < 2*n; j++) {
			if (ppl[i] == ppl[j]) {
				ppls[i] = person(i);
				ppls[j] = person(j);
				ppls[i].set(ppls[j]);
				ppls[j].set(ppls[i]);
			}
		}
	}

	int ans = 0;

	for (int i = 0; i < 2*n; i++) {
		if (!ppls[i].paired) {
			ans += abs(ppls[i].dist());
			int midsum = 0;
			for (int j = i + 1; j < (ppls[i].partner)->pos; j++) {
				midsum += ppls[j].dist();
			}

			if (midsum >= 0) {
				backswap(ppls, ppls[i].partner->pos, ppls[i].pos + 1);
			} else {
				frontswap(ppls, ppls[i].pos, ppls[i].partner->pos - 1);
			}

			ppls[i].paired = true;
			ppls[i].partner->paired = true;
		}
	}

	cout << ans << "\n";
}

		 
