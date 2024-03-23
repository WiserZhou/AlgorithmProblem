#include <iostream>
#include <vector>
#include <algorithm> // 添加头文件以使用std::max_element
#include <cassert>   // 添加头文件以使用assert宏

// Counting Sort 算法实现
void countingSort(std::vector<int> &A, int k)
{
    // 初始化计数数组C，大小为k+1
    std::vector<int> C(k + 1, 0);

    // 统计每个元素出现的次数
    for (std::vector<int>::size_type i = 0; i < A.size(); ++i)
    {
        // 验证A[i]的值在0到k之间
        assert(A[i] >= 0 && A[i] <= k);
        C[A[i]]++;
    }

    // 计算每个元素累计出现的次数
    for (int i = 1; i <= k; ++i)
    {
        C[i] += C[i - 1];
    }

    // 创建一个新的输出数组B，用于存放排序后的元素
    std::vector<int> B(A.size());

    // 正向遍历输入数组A，根据计数数组C计算每个元素在输出数组B中的位置并放置
    for (std::vector<int>::size_type i = 0; i < A.size(); ++i)
    {
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--;
    }

    // 将排序好的B数组复制回原数组A
    A = B;
}

// 测试Counting Sort
int main()
{
    std::vector<int> arr = {4, 2, 2, 8, 3, 3, 1};
    int max_val = *std::max_element(arr.begin(), arr.end()); // 获取arr中的最大值，作为k值

    countingSort(arr, max_val);

    // 输出排序后的数组
    std::cout << "Sorted array: ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << "\n";

    return 0;
}