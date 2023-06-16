#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<bool> > friends;
vector<vector<int> > groups;
vector<bool> visited;
vector<int> cur;

void floodfill(int x);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	friends = vector<vector<bool> >(N, vector<bool>(N, false));
	visited = vector<bool>(N, false);

	for (int i = 0; i < M; i++) {
		int x, y; cin >> x >> y;
		x--;
		y--;
		friends[x][y] = true;
		friends[y][x] = true;
	}

	for (int i = 0; i < N; i++) {
		if (!visited[N]) {
			floodfill(i);
		}
	}

	for (int i = 0; i < groups.size(); i++) {
		for (int j = 0; j < groups[i].size(); j++) {
			for (int k = j + 1; k < groups[i].size(); k++) {
				if (!friends[groups[i][j]][groups[i][k]]) {
					cout << "NO\n";
					return 0;
				}
			}
		}
	}

	cout << "YES\n";
	return 0;
}

void floodfill(int x) {
	visited[x] = true;
	cur.push_back(x);
	int addCount = 0;
	for (int i = 0; i < N; i++) {
		if (friends[x][i] && !visited[i]) {
			addCount++;
			floodfill(i);
		}
	}

	if (addCount == 0) {
		groups.push_back(cur);
		cur = vector<int>();
	}
}
