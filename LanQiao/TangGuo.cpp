#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int n, m, k, dp[1 << 20], v[1 << 20]; // 状压的数组需要开2^n，因为表示的是状态，每种口味的状态，如果有这种状态那么就是1，
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    memset(dp, 0x3f3f3f3f, sizeof(dp));
    for (int i = 1; i <= n; ++i)
    {
        int h = 0, p;
        for (int j = 1; j <= k; ++j) // 遍历每包糖果中每个糖果的口味
        {
            scanf("%d", &p);
            p--;              // 第一种口味的糖果对应二进制位2^0
            h = h | (1 << p); // 这里不能用+，一包糖里可能有多种同一口味的，把口味并进去
        }
        dp[h] = 1; // 设置这包糖果的搭配对应的状态为1
        v[i] = h;  // 记录第i包糖果的状态
    }
    for (int i = 0; i < (1 << m); ++i) // i枚举的是状态，即0～1...11111（m个1）
    {
        for (int j = 1; j <= n; ++j) // 遍历每包糖果
        {
            dp[i | v[j]] = min(dp[i | v[j]], dp[i] + 1); // 第i个状态合并上第j包糖果的状态之后的值等于合并之后的包数和这个状态直接加上一包后包数的最小值
        }
    }
    if (dp[(1 << m) - 1] == 0x3f3f3f3f) // 如果全部都有的状态的值是无穷大，那么表示遍历的时候没有碰到他，也就是说搭配不出来
        cout << -1;                     // 搭配不出来
    else
        cout << dp[(1 << m) - 1]; // 搭配出来
    return 0;
}