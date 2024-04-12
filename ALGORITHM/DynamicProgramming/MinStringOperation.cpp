#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string X, Y;
    cin >> X >> Y;
    // cin>>t;
    int m = X.size();
    int n = Y.size();
    vector<vector<int>> E(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> B(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; i++)
    {
        E[i][0] = i; // 有一个字符串长度是0的时候，操作数就是另一个字符串的长度
    }
    for (int i = 0; i < n; i++)
    {
        E[0][i] = i;
    }
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (X[i] == Y[j])
            {
                E[i][j] = E[i - 1][j - 1]; // 如果相同，那么就不需要修改
            }
            else
            {
                E[i][j] = E[i - 1][j - 1] + 1;
            }
            B[i][j] = 3;
            if (E[i][j] > E[i - 1][j] + 1) // 比较是否当前位置的编辑代价中和上一位的是否重叠
            {
                E[i][j] = E[i - 1][j] + 1;
                B[i][j] = 2;
            }
            if (E[i][j] > E[i][j - 1] + 1)
            {
                E[i][j] = E[i][j - 1] + 1;
                B[i][j] = 1;
            }
            // if (E[i][j] >= t) //最小编辑距离判别问题
            // {
            //     B[i][j]=4;
            //     break;
            // }
        }
    }
}