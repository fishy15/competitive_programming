#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n, m; cin >> n >> m;
	vector<int> t; 

	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		t.push_back(x);
	}

	int sign = -1;
	vector<int> c;
	c.push_back(t[0]);
	
	for (int i = 0; i < n - 1; i++) {
		int x = t[i + 1] - t[i];
		c.push_back(sign*x);
		sign *= -1;
	}

	c.push_back(sign * (m - t[n - 1]));

	int prevLit = 0;
	int fovLit = 0;
	int fovDim = 0;

	/*
	for (int i : c) {
		cout << i << ' ';
	} 
	cout << endl;
	*/

	for (int i = 0; i < c.size(); i++) {
		if (c[i] > 0) {
			fovLit += c[i];
		} else {
			fovDim += -1 * c[i];
		}
	}

	//cout << fovLit << ' ' << fovDim << "!!!" << endl;

	int max = fovLit;

	for (int i = 0; i < c.size(); i++) {
		// calc for next
		if (c[i] > 0) {
			prevLit += c[i];
			fovLit -= c[i];
		} else {
			fovDim += c[i];
		}

		//cout << "prev: " << prevLit << endl;
		//cout << "dim: " << fovDim << endl;
		if (c[i] == 1 || c[i] == -1) {
			continue;
		}

		int x = prevLit;

		if (c[i] > 0) {
			x += fovDim;
			x--;
		} else {
			x += fovDim;
			x -= c[i];
			x--;
		}

		//cout << i << ' ' << x << endl;

		if (x > max) {
			max = x;
		}
	}

	cout << max << '\n';

	return 0;
}


