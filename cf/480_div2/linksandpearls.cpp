#include <iostream>
#include <string>

using namespace std;

int main() 
{
	string s; cin >> s; 
	int l = 0, o = 0; 
	for (int i = 0; i < s.size(); i++) 
	{
		if (s[i] == '-')
			l++;
		else
			o++;
	}
	
	if (o == 0) 
		cout << "yes\n";
	else if (l % o == 0)
		cout << "yes\n";
	else
		cout << "no\n";

	return 0;
}
