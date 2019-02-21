#include <iostream>
#include <vector>

#define vi vector<int>
#define vb vector<bool>

using namespace std;

int N;

int solve(int i);

typedef struct person person;

struct person {
	int dist;
	int up; 

	person(int up) {
		this->up = up - 1;
		if (up == -1) {
			dist = 1;
		} else {
			dist = -1;
		}
	}
};

vector<person> ppl;

int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		int x; cin >> x;
		ppl.push_back(person(x));
	}

	int max = 0;
	for (int i = 0; i < N; i++) {
		int s = solve(i);
		max = s > max ? s : max;
	}

	cout << max << '\n';

	return 0;
}

int solve(int i) {
	if (ppl[i].dist == -1) {
		ppl[i].dist = solve(ppl[i].up) + 1;
	}

	return ppl[i].dist;
}
