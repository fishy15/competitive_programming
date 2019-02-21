#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int n; cin >> n;
    vector<string> board;
    for (int i = 0; i < n + 2; i++) 
    {
        if (i == 0 || i == n + 1)
        {
            string row;
            for (int j = 0; j < n + 2; j++)
            {
                row += 'x';
            }
            
            board.push_back(row);
            continue;
        }
        string row; cin >> row;
        row = 'x' + row + 'x';
        board.push_back(row);
    }
    
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            int oCount = 0;
            if (board[i + 1][j] == 'o')
            {
                oCount++;
            }
            
            if (board[i][j + 1] == 'o')
            {
                oCount++;
            }
            
            if (board[i - 1][j] == 'o')
            {
                oCount++;
            }
            
            if (board[i][j - 1] == 'o')
            {
                oCount++;
            }
            
            if (oCount % 2 != 0) 
            {
                cout << "NO\n";
                return 0;
            }
        }
    }
    cout << "YES\n";
    return 0;
}
