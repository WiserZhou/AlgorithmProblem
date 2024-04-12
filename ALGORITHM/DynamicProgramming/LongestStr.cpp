#include <iostream>
#include <vector>

using namespace std;

pair<int, vector<int>> longestIncreasingSubsequence(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return {0, {}};

    // dp[i] 表示以 nums[i] 结尾的最长增长子序列的长度
    vector<int> dp(n, 1);
    vector<vector<int>> sequences(n);

    // 动态规划转移方程
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (nums[i] > nums[j]) // 如果满足递增
            {
                if (dp[i] < dp[j] + 1)
                {
                    dp[i] = dp[j] + 1;
                    sequences[i] = sequences[j]; // 记录之前的序列
                }
            }
        }
        sequences[i].push_back(nums[i]); // 添加上当前序列
    }

    // 找到 dp 中的最大值
    int maxLength = 0;
    int maxIndex = 0;
    for (int i = 0; i < n; ++i)
    {
        if (dp[i] > maxLength)
        {
            maxLength = dp[i];
            maxIndex = i;
        }
    }

    return {maxLength, sequences[maxIndex]};
}

int main()
{
    vector<int> nums = {5, 2, 8, 6, 3, 6, 9, 7}; // 示例输入序列
    auto result = longestIncreasingSubsequence(nums);
    int length = result.first;
    vector<int> lis = result.second;

    cout << "The length of the longest increasing subsequence is: " << length << endl;
    cout << "The longest increasing subsequence is: ";
    for (int num : lis)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
