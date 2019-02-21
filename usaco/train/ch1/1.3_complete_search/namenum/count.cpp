#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
	ifstream fin("dict.txt");
	int n = 0;
	while(1) {
		n++;
		string s;
		fin >> s;
		cout << s << " " << n << endl;
	}
	return 0;
}
