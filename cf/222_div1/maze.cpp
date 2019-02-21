#include <iostream>
#include <vector>
#include <string>

using namespace std;

void 
int neighbor(int x, int y);

int N, M, K;
vector<vector<int> > nextto;
vector<string> board;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M >> K;
	for (int i = 0; i < N; i++) {
		string s; cin >> s;
		board.push_back(s);
	}

	nextto = vector<vector<int> >(N, vector<int>(M, -1));

	for (int i = 0; i < K; i++) {

