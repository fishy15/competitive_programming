#include <iostream>
#include <vector>

using namespace std;

typedef struct node node;

struct node {
	vector<int> child;
	bool cat;
	bool visited;
	int catCount;

	node(int num) {
		if (num == 0) {
			cat = false;
		} else {
			cat = true;
		}

		catCount = 0;
		visited = false;
	}
};

int N, M;
vector<node> park;
int ans;

void dfs(int loc, int prevCount);

int main() {
	cin >> N >> M;
	park.push_back(node(0));
	for (int i = 0; i < N; i++) {
		int x; cin >> x;
		park.push_back(node(x));
	}

	for (int i = 0; i < N - 1; i++) {
		int x, y; cin >> x >> y;
		park[x].child.push_back(y);
		park[y].child.push_back(x);
	}

	dfs(1, 0);

	cout << ans << '\n';

	return 0;
}

void dfs(int loc, int prevCount) {
	//cout << loc << " prev: " << prevCount << endl;
	node* cur = &park[loc];
	cur->visited = true;
	if (cur->cat) {
		cur->catCount = prevCount + 1;
		if (cur->catCount > M) {
			return;
		}
	} else {
		cur->catCount = 0;
	}

	bool end = true;

	for (int i = 0; i < cur->child.size(); i++) {
		end = end && park[cur->child[i]].visited;
	}

	if (end) {
		//cout << loc << " has resto\n";
		ans++;
	} else {
		for (int i = 0; i < cur->child.size(); i++) {
			if (!park[cur->child[i]].visited) {
				dfs(cur->child[i], cur->catCount);
			}
		}
	}
	cur->visited = false;
}
