// 引入所需的头文件，包括iostream用于输入输出，vector用于动态数组，algorithm用于排序和其他算法
#include <iostream>
#include <vector>
#include <algorithm>

// 使用std命名空间以简化代码
using namespace std;

// 划分函数：将输入数组nums按照固定大小的子集进行划分，并计算每个子集的中位数，存放在medians向量中
vector<int> partition(vector<int> &nums, int n)
{
    // 计算有多少个子集（假设每个子集包含5个元素）
    int groupSize = n / 5;
    vector<int> medians; // 创建一个向量用来存储各个子集的中位数

    // 对于每个子集
    for (int i = 0; i < groupSize; i++)
    {
        // 使用nth_element函数对当前子集进行部分排序，使得子集中间位置的元素处于正确的位置
        std::nth_element(nums.begin() + i * 5, nums.begin() + min((i + 1) * 5, n), nums.begin() + i * 5 + 2);

        // 把当前子集的中位数添加到medians向量中（在部分排序后，第三个元素即为中位数）
        medians.push_back(nums[i * 5 + 2]);
    }

    // 处理最后一个子集不足5个元素的情况
    if (n % 5 != 0)
    {
        // 对剩余元素进行部分排序，并找到剩余元素的中位数
        std::nth_element(nums.begin() + groupSize * 5, nums.end(), nums.begin() + groupSize * 5 + (n - groupSize * 5) / 2);

        // 将剩余元素的中位数添加到medians向量中
        medians.push_back(nums[groupSize * 5 + (n - groupSize * 5) / 2]);
    }

    return medians; // 返回包含所有子集中位数的向量
}

// 寻找第k小的元素的函数
int findKthSmallest(vector<int> &nums, int n, int k)
{
    // 递归终止条件：当只剩下一个元素时，返回该元素作为结果
    if (n == 1)
    {
        return nums[0];
    }

    // Step 1: 划分阶段
    vector<int> medians = partition(nums, n);

    // Step 2: 计算中位数的中位数（即medians向量的中位数）
    int p = findKthSmallest(medians, medians.size(), medians.size() / 2);

    // Step 3: 根据中位数p将原始数组nums划分为三个子集：小于p的元素集s1，等于p的元素集s2，大于p的元素集s3
    vector<int> s1, s2, s3;
    for (int num : nums)
    {
        if (num < p)
        {
            s1.push_back(num);
        }
        else if (num == p)
        {
            s2.push_back(num);
        }
        else
        {
            s3.push_back(num);
        }
    }

    // Step 4: 在适当子集中递归查找第k小的元素
    int m1 = s1.size(); // 计算小于p的元素数量
    if (m1 >= k)        // 若第k小的元素在s1中
    {
        return findKthSmallest(s1, m1, k);
    }
    else if (m1 + s2.size() >= k) // 若第k小的元素为中位数p或者在s2中
    {
        return p;
    }
    else // 若第k小的元素在s3中
    {
        return findKthSmallest(s3, s3.size(), k - m1 - s2.size()); // 更新k的值，继续在s3中查找
    }
}

int main()
{
    // 示例数据
    vector<int> nums = {3, 5, 1, 8, 2, 7, 4, 9, 6};
    int n = nums.size(); // 数组元素总数
    int k = 2;           // 要找的第k小的元素

    // 调用findKthSmallest函数获取结果
    int res = findKthSmallest(nums, n, k);
    cout << "The " << k << "th smallest element is: " << res << endl;

    return 0; // 程序结束
}