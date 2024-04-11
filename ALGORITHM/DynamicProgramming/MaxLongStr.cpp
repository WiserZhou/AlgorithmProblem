#include <iostream>
#include <string>
#include <vector>
using namespace std;
void PrintLCS(const vector<vector<string>> &flag, const string &str1, int i, int j)
{
    if (i == 0 || j == 0)
        return;
    else
    {
        if (flag[i][j] == "3")
        {
            PrintLCS(flag, str1, i - 1, j - 1);
            cout << str1[i - 1];
        }
        else
        {
            if (flag[i][j] == "1")
            {
                PrintLCS(flag, str1, i, j - 1);
            }
            else
                PrintLCS(flag, str1, i - 1, j);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string str1, str2;
    cin >> str1 >> str2;
    int m = str1.size();
    int n = str2.size();
    vector<vector<int>> matrix(m + 1, vector<int>(n + 1, 0));
    vector<vector<string>> flag(m + 1, vector<string>(n + 1, "0"));

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
                flag[i][j] = "3";
            }
            else if (matrix[i][j - 1] > matrix[i - 1][j])
            {
                matrix[i][j] = matrix[i][j - 1];
                flag[i][j] = "1"; // 上
            }
            else
            {
                matrix[i][j] = matrix[i - 1][j];
                flag[i][j] = "2"; // 左
            }
        }
    }
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--------------------" << endl;
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cout << flag[i][j] << " ";
        }
        cout << endl;
    }
    PrintLCS(flag, str1, m, n);
    return 0;
}
/**
ABCBDAB
BDCABA
*/
