#include <iostream>
#include <vector>

using namespace std;

void bfs();

int N;
vector<int> height;
vector<int> width;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	for (int i = 0; i < N; i++) {
		int x, y; cin >> x >> y;
		height.push_back(x);
		width.push_back(y);
	}

	int min = 1000000001;
	for (int i = 0; i < N; i++) {
		//cout << min << endl;
		if (height[i] <= min) {
			if (width[i] <= min) {
				min = height[i] > width[i] ? height[i] : width[i];
			} else {
				min = height[i];
			}
		} else {
			if (width[i] <= min) {
				min = width[i];
			} else {
				cout << "NO\n";
				return 0;
			}
		}
		//cout << min << endl;
	}

	cout << "YES\n";
	return 0;
}
