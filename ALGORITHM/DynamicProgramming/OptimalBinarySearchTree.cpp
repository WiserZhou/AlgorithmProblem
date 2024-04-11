#include <iostream>
#include <vector>
using namespace std;
void PrintBST(vector<vector<int>> &Root, int i, int j)
{
    if (i > j)
    {
        cout << " d[" << j << "] ";
        return;
    }
    int L = Root[i][j];
    cout << " ";
    PrintBST(Root, i, L - 1);
    cout << " ";
    cout << " k[" << L << "] ";
    cout << " ";
    PrintBST(Root, L + 1, j);
    cout << " ";
}
int main()
{
    int n;
    cin >> n;
    vector<int> q(n + 2, 0);
    vector<int> p(n + 2, 0);
    for (int i = 0; i <= n; i++)
    {
        cin >> q[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }
    vector<vector<int>> E(n + 2, vector<int>(n + 2, 0));
    vector<vector<int>> W(n + 2, vector<int>(n + 2, 0));
    vector<vector<int>> Root(n + 2, vector<int>(n + 2, 0));
    for (int i = 1; i <= n + 1; i++)
    {
        E[i][i - 1] = q[i - 1]; // 表示i到i-1的代价为d(i-1)的概率
        W[i][i - 1] = q[i - 1];
    }
    for (int l = 1; l <= n; l++) // 表示沿对角线方向的斜线
    {
        for (int i = 1; i <= n - l + 1; i++) // 表示从左上方第一个开始往右下方的行数递增
        {
            int j = i + l - 1; // 表示随着i的递增，j也递增，从而使用i，j表示对角线方向上的一条线的对象
            E[i][j] = INT_MAX;
            W[i][j] = W[i][j - 1] + p[j] + q[j]; // 表示W的递推公式，从（i，j-1）到（i，j）的概率增加
            for (int r = i; r <= j; r++)
            {
                int t = E[i][r - 1] + E[r + 1][j] + W[i][j];
                if (t < E[i][j])
                {
                    E[i][j] = t;
                    Root[i][j] = r;
                }
            }
        }
    }

    PrintBST(Root, 0, n);
    return 0;
}