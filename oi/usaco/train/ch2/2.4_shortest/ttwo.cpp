/*
ID: aaryan.1
TASK: ttwo
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define MAX_VISIT 200
#define BOARD_SZ 10

using namespace std;

typedef struct thingy thingy;

vector<string> board;

struct thingy {
	int x, y, dir;
	int visit[BOARD_SZ][BOARD_SZ];

	thingy() {
		x = 0;
		y = 0;
		dir = 0;
	}

	thingy(int x, int y) {
		this->x = x;
		this->y = y;
		dir = 0;
		for (int i = 0; i < BOARD_SZ; i++) {
			for (int j = 0; j < BOARD_SZ; j++) {
				visit[i][j] = 0;
			}
		}
	}

	void rotate() {
		dir++;
		dir %= 4;
	}

	void move() {
		if (dir == 0) {
			if (x > 0 && board[x - 1][y] != '*') {
				x--;
			} else {
				rotate();
			}
		} else if (dir == 1) {
			if (y < BOARD_SZ - 1 && board[x][y + 1] != '*') {
				y++;
			} else {
				rotate();
			}
		} else if (dir == 2) {
			if (x < BOARD_SZ - 1 && board[x + 1][y] != '*') {
				x++;
			} else {
				rotate();
			}
		} else {
			if (y > 0 && board[x][y - 1] != '*') {
				y--;
			} else {
				rotate();
			}
		}

		visit[x][y]++;
	}

	bool check() {
		return visit[x][y] > MAX_VISIT;
	}
};

int main() {
	ifstream fin("ttwo.in");
	ofstream fout("ttwo.out");

	thingy farmer, cow;
	for (int i = 0; i < BOARD_SZ; i++) {
		string s; fin >> s;
		board.push_back(s);
		for (int j = 0; j < BOARD_SZ; j++) {
			if (s[j] == 'F') {
				farmer = thingy(i, j);
			} else if (s[j] == 'C') {
				cow = thingy(i, j);
				//cout << "loc: " << j << ' ' << i << '\n';
			}
		} 
	}

	int genCount = 1;
	while (genCount > 0) {
		farmer.move();
		cow.move();
		//printf("gen: %d\n", genCount);
		//printf("farmer: %d %d\ncow: %d %d\n", farmer.x, farmer.y, cow.x, cow.y);
		if (farmer.x == cow.x && farmer.y == cow.y) {
			//cout << "they met.\n";
			break;
		} else if (farmer.check() || cow.check()) {
			//cout << "they will never meet.\n";
			//cout << "farmer: " << farmer.visit[farmer.x][farmer.y] << endl;
			//cout << "cow: " << cow.visit[cow.x][cow.y] << endl;
			genCount = -1;
		} 

		genCount++;
	}

	fout << genCount << '\n';

	return 0;
}

