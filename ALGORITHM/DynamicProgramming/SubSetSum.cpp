#include <iostream>
#include <vector>

using namespace std;

bool subsetSum(vector<int> &nums, int P)
{
    int n = nums.size();
    if (n == 0)
        return false;

    // dp[i][j] 表示前i个元素能否组成和为j
    vector<vector<bool>> dp(n + 1, vector<bool>(P + 1, false));

    // 初始化第0列为true，表示和为0的情况
    for (int i = 0; i <= n; ++i)
    {
        dp[i][0] = true;
    }

    // 动态规划转移方程
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= P; ++j)
        {
            if (j >= nums[i - 1]) // 如果还可以放得下nums[i-1]
            {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]]; // 要么不放进去，要么放进去减去他的大小
            }
            else
            {
                dp[i][j] = dp[i - 1][j]; // 放不下就直接不放进去
            }
        }
    }

    return dp[n][P];
}

int main()
{
    vector<int> nums = {3, 34, 4, 12, 5, 2}; // 示例输入序列
    int P = 9;                               // 示例目标和
    bool result = subsetSum(nums, P);
    if (result)
    {
        cout << "True, there exists a subset whose sum is " << P << "." << endl;
    }
    else
    {
        cout << "False, there is no subset whose sum is " << P << "." << endl;
    }
    return 0;
}
