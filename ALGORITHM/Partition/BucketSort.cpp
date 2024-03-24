#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

// 桶排序算法
void bucketSort(vector<double> &A)
{
    int n = A.size();          // 数组长度
    vector<list<double>> B(n); // 创建 n 个桶，每个桶是一个链表

    // 将输入元素分配到对应的桶中
    for (int i = 0; i < n; ++i)
    {
        int bucket_index = static_cast<int>(n * A[i]); // 计算元素应该放入的桶的索引
        B[bucket_index].push_back(A[i]);               // 将元素添加到对应的桶中
    }

    // 对每个桶中的元素进行排序（使用插入排序）
    for (int i = 0; i < n; ++i)
    {
        B[i].sort(); // 使用链表的 sort 方法进行排序
    }

    // 将排序后的元素依次放回原数组
    int index = 0;
    for (int i = 0; i < n; ++i)
    {
        for (double num : B[i])
        {
            A[index++] = num; // 将排序后的元素放回原数组
        }
    }
}

int main()
{
    // 示例输入
    vector<double> A = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};

    cout << "Original Array: ";
    for (double num : A)
        cout << num << " ";
    cout << endl;

    // 执行桶排序算法
    bucketSort(A);

    cout << "Sorted Array: ";
    for (double num : A)
        cout << num << " ";
    cout << endl;

    return 0;
}
