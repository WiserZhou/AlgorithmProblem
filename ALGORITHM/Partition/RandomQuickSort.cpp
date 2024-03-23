#include <iostream>
#include <algorithm> // 为了使用swap
#include <cstdlib>   // 为了使用rand()和srand()
#include <ctime>     // 为了使用time()
#include <vector>
using namespace std;

// 交换数组中两个元素的值
void swap(vector<int> &A, int i, int j)
{
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

// Partition函数，返回枢轴元素的最终位置
int Partition(vector<int> &A, int p, int r)
{
    int x = A[r];  // 选取最后一个元素作为枢轴
    int i = p - 1; // 初始化左指针

    for (int j = p; j <= r - 1; ++j)
    {
        if (A[j] <= x)
        {                  // 如果当前元素小于等于枢轴
            i++;           // 左指针右移
            swap(A, i, j); // 交换当前元素与左指针指向的元素
        }
    }
    swap(A, i + 1, r); // 将枢轴元素放到正确的位置

    return i + 1; // 返回枢轴元素的位置
}

// 随机分区函数
int RandomPartition(vector<int> &A, int p, int r)
{
    srand(time(0));                   // 设置随机种子
    int i = rand() % (r - p + 1) + p; // 在区间[p, r]内随机选择一个位置i
    swap(A[r], A[i]);                 // 将A[r]与A[i]交换

    return Partition(A, p, r);
}

// 假设Partition函数已经实现，它应该返回分区后的枢轴索引
// 这里假设Partition函数接收数组、起始索引和结束索引，并完成分区操作
// （这里省略了Partition的具体实现）

// 随机化快速排序函数
void RandomizedQuickSort(vector<int> &A, int p, int r)
{
    if (p < r)
    {
        int q = RandomPartition(A, p, r);
        RandomizedQuickSort(A, p, q - 1);
        RandomizedQuickSort(A, q + 1, r);
    }
}

int main()
{
    vector<int> A = {9, 7, 5, 11, 12, 2, 14, 3, 10, 6};
    int n = A.size();
    RandomizedQuickSort(A, 0, n - 1);
    // 打印排序后的数组
    for (int i : A)
    {
        cout << i << " ";
    }
    return 0;
}