#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N, M;
vector<string> board;

void floodfill(int x, int y, bool white);

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		string x; cin >> x;
		board.push_back(x);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			floodfill(i, j, false);
		}
	}

	for (int i = 0; i < N; i++) {
		cout << board[i] << '\n';
	}

	return 0;
}

void floodfill(int x, int y, bool white) {
	//cout << x << ' ' << y << endl;
	//cout << (white ? 'W' : 'B') << endl;
	if (board[x][y] != '.') {
		return;
	}

	if (white) {
		board[x][y] = 'W';
	} else {
		board[x][y] = 'B';
	}

	if (x > 0) {
		floodfill(x - 1, y, !white);
	}

	if (x < N - 1) {
		floodfill(x + 1, y, !white);
	}

	if (y > 0) {
		floodfill(x, y - 1, !white);
	}

	if (y < M - 1) {
		floodfill(x, y + 1, !white);
	}
}
