#include <iostream>
#include <vector>
using namespace std;

// 在两个有序数组中寻找第k小的数
int findKth(vector<int> &nums1, int start1, vector<int> &nums2, int start2, int k)
{
    int m = nums1.size();
    int n = nums2.size();

    // 边界情况处理

    // 如果 nums1 的起始索引超出数组范围，则直接返回 nums2 中的第 k 小的数
    if (start1 >= m)
    {
        return nums2[start2 + k - 1];
    }
    // 如果 nums2 的起始索引超出数组范围，则直接返回 nums1 中的第 k 小的数
    if (start2 >= n)
    {
        return nums1[start1 + k - 1];
    }
    // 如果 k 等于 1，则返回 nums1 和 nums2 中起始索引处较小的数
    if (k == 1)
    {
        return min(nums1[start1], nums2[start2]);
    }

    // 正常情况处理

    // 计算 nums1 和 nums2 中间位置的索引
    int mid1 = start1 + k / 2 - 1;
    int mid2 = start2 + k / 2 - 1;

    // 获取 nums1 和 nums2 中间位置的值，若超出数组范围，则赋予一个足够大的值
    int val1 = mid1 < m ? nums1[mid1] : INT_MAX;
    int val2 = mid2 < n ? nums2[mid2] : INT_MAX;

    // 递归调用 findKth 函数，并根据比较结果更新起始索引和 k 的值
    if (val1 <= val2)
    {
        return findKth(nums1, mid1 + 1, nums2, start2, k - (mid1 - start1 + 1)); // 计算nums1的一半取值加在中位数值索引上
    }
    else
    {
        return findKth(nums1, start1, nums2, mid2 + 1, k - (mid2 - start2 + 1));
    }
}

// 寻找两个有序数组的中位数
double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
{
    int m = nums1.size();
    int n = nums2.size();
    int total = m + n;

    // 根据总长度的奇偶性，分别计算中位数
    if (total % 2 == 1)
    {
        return findKth(nums1, 0, nums2, 0, total / 2 + 1);
    }
    else
    {
        return (findKth(nums1, 0, nums2, 0, total / 2) + findKth(nums1, 0, nums2, 0, total / 2 + 1)) / 2.0;
    }
}

int main()
{
    // 示例输入
    vector<int> nums1 = {1, 3, 4, 5};
    vector<int> nums2 = {2};

    // 调用函数并输出结果
    cout << "Median is: " << findMedianSortedArrays(nums1, nums2) << endl;

    return 0;
}
