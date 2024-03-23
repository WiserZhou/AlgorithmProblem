#include <iostream>
#include <vector>
using namespace std;

pair<int, int> MaxMin(const vector<int> &A, int i, int j)
{
    // 输出函数，返回一个包含最小值和最大值的pair
    if (j - i + 1 == 1)
    {
        return make_pair(A[i], A[i]); // 当数组只有一个元素时，最大值和最小值都是该元素
    }
    else if (j - i + 1 == 2)
    {
        int minVal = min(A[i], A[j]);
        int maxVal = max(A[i], A[j]);
        return make_pair(minVal, maxVal); // 当数组有两个元素时，比较并返回最大值和最小值
    }

    // 当数组有更多元素时，进行分治
    int k = (j + i) / 2;
    pair<int, int> leftResult = MaxMin(A, i, k);      // 计算左半部分的最大值和最小值
    pair<int, int> rightResult = MaxMin(A, k + 1, j); // 计算右半部分的最大值和最小值

    int minVal = min(leftResult.first, rightResult.first);   // 计算整个数组的最小值
    int maxVal = max(leftResult.second, rightResult.second); // 计算整个数组的最大值

    return make_pair(minVal, maxVal); // 返回最小值和最大值组成的pair
}

// 测试函数
void testMaxMin()
{
    vector<int> A = {1, 5, 3, 9, 2, 7};
    int i = 0, j = A.size() - 1;
    pair<int, int> result = MaxMin(A, i, j);
    cout << "Minimum Value: " << result.first << ", Maximum Value: " << result.second << endl;
}

int main()
{
    testMaxMin();
    return 0;
}