#include <iostream>
#include <vector>

using namespace std;

int N;
int maxX, maxY;
int num = 1;
vector<vector<int> > points;

void floodfill(int x, int y);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	points = vector<vector<int> >(1001, vector<int>(1001, 0));
	for (int i = 0; i < N; i++) {
		int x, y; cin >> x >> y;
		if (x > maxX) {
			maxX = x;
		}

		if (y > maxY) {
			maxY = y;
		}

		points[x][y] = -1;
	}

	maxX++;
	maxY++;

	int num = 1;
	for (int x = 0; x < maxX; x++) {
		for (int y = 0; y < maxY; y++) {
			if (points[x][y] == -1) {
				floodfill(x, y);
				num++;
			}
		}
	}

	cout << num - 2 << '\n';

	return 0;
}

void floodfill(int x, int y) {
	points[x][y] = num;

	int xtemp = x;
	int ytemp = y;

	while (xtemp >= 0) {
		if (points[xtemp][y] == -1) {
			floodfill(xtemp, y);
			break;
		}

		xtemp--;
	}

	xtemp = x;

	while (xtemp < maxX) {
		if (points[xtemp][y] == -1) {
			floodfill(xtemp, y);
			break;
		}

		xtemp++;
	}

	while (ytemp >= 0) {
		if (points[x][ytemp] == -1) {
			floodfill(x, ytemp);
			break;
		}

		ytemp--;
	}

	ytemp = y;

	while (ytemp < maxY) {
		if (points[x][ytemp] == -1) {
			floodfill(x, ytemp);
			break;
		}

		ytemp++;
	}
}
