#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int n, C;
    cin >> n >> C;
    vector<int> w(n, 0);
    vector<int> v(n, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i] >> v[i];
    }
    vector<vector<int>> m(n + 1, vector<int>(C + 1, 0)); // 表示把从i序号的物品之后的装填剩余的空间j能获得的最大价值
    for (int j = 0; j < w[n]; j++)
    {
        m[n][j] = 0; // 表示把n号物品放进去，剩余的空间小于n号所需的空间，那么一个放不进去，价值都是0
    }
    for (int j = w[n]; j <= C; j++)
    {
        m[n][j] = v[n]; // 剩余空间足够，就可以放进去
    }
    for (int i = n - 1; i >= 2; i--)
    {
        for (int j = 0; j <= w[i] - 1; j++)
        {
            m[i][j] = m[i + 1][j]; // 剩余空间不足放i号物品
        }
        for (int j = w[i]; j <= C; j++)
        {
            m[i][j] = max(m[i + 1][j], m[i + 1][j - w[i]] + v[i]); // 剩余空间足够放下i号物品，取不放i号物品和放下i号物品后剩余空间可以获得最大价值和i号物品的价值之和的最大值
        }
    }
    if (C < w[1])
    {
        m[1][C] = m[2][C];
    }
    else
    {
        m[1][C] = max(m[2][C], m[2][C - w[1]] + v[1]);
    }
}