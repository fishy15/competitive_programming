/*
ID: aaryan.1
TASK: castle
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#define vi vector<int>
#define vii vector<vector<int>>

using namespace std;

void floodfill(int num, vii &walls, vii &rooms, int i, int j);

int main() {
	ifstream fin("castle.in");
	ofstream fout("castle.out");

	int m, n; fin >> m >> n;
	vii house;

	for (int i = 0; i < n; i++) {
		vi row;
		for (int j = 0; j < m; j++) {
			int x; fin >> x;
			row.push_back(x);
		}

		house.push_back(row);
	}

	vii rooms(n, vi(m, -1));

	int roomNum = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (rooms[i][j] > -1) {
				continue;
			}

			floodfill(roomNum, house, rooms, i, j);
			roomNum++;
		}
	}

	vi size(roomNum);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			//cout << rooms[i][j] << " ";
			size[rooms[i][j]]++;
		} 
		//cout << endl;
	}

	int maxOne = 0;
	int maxCombo = 0;
	int maxI = -1;
	int maxJ = -1;
	char maxDir = 'X';

	for (int j = m - 1; j >= 0; j--) {
		for (int i = 0; i < n; i++) {
			if (size[rooms[i][j]] > maxOne) {
				maxOne = size[rooms[i][j]];
			}

			if (j < m - 1) {
				if (rooms[i][j] != rooms[i][j + 1]) {
					//cout << "east " << i << " " << j << endl;
					int combo = size[rooms[i][j]] + size[rooms[i][j + 1]];
					//cout << combo << endl;
					if (combo >= maxCombo) {
						maxCombo = combo;
						maxI = i;
						maxJ = j;
						maxDir = 'E';
					}
				}
			}

			if (i > 0) {
				if (rooms[i][j] != rooms[i - 1][j]) {
					//cout << "north " << i << " " << j << endl;
					int combo = size[rooms[i][j]] + size[rooms[i - 1][j]];
					//cout << combo << endl;
					if (combo >= maxCombo) {
						maxCombo = combo;
						maxI = i;
						maxJ = j;
						maxDir = 'N';
					}
				}
			}
		}
	}

	fout << roomNum << '\n';
	fout << maxOne << '\n';
	fout << maxCombo << '\n';
	fout << maxI + 1 << ' ' << maxJ + 1 << ' ' << maxDir << '\n';

	return 0;
}

void floodfill(int num, vii &walls, vii &rooms, int i, int j) {
	//cout << i << " " << j << endl;
	rooms[i][j] = num;

	if (walls[i][j] % 2 == 0 && j > 0 && rooms[i][j - 1] == -1) {
		//cout << "east\n";
		floodfill(num, walls, rooms, i, j - 1);
	}

	if ((walls[i][j] / 2) % 2 == 0 && i > 0 && rooms[i - 1][j] == -1) {
		floodfill(num, walls, rooms, i - 1, j);
	}

	if ((walls[i][j] / 4) % 2 == 0 && j < rooms[0].size() - 1 && rooms[i][j + 1] == -1) {
		floodfill(num, walls, rooms, i, j + 1);
	}

	if ((walls[i][j] / 8) % 2 == 0 && i < rooms.size() - 1 && rooms[i + 1][j] == -1) {
		floodfill(num, walls, rooms, i + 1, j);
	}
}

	

