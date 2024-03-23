#include <iostream>
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

// 快速排序函数
void QuickSort(vector<int> &A, int p, int r)
{
    if (p < r)
    {
        int q = Partition(A, p, r);
        QuickSort(A, p, q - 1); // 递归排序左子数组
        QuickSort(A, q + 1, r); // 递归排序右子数组
    }
}

// 测试函数
void testQuickSort()
{
    vector<int> A = {9, 7, 5, 11, 12, 2, 14, 3, 10, 6};
    int p = 0;
    int r = A.size() - 1;

    QuickSort(A, p, r);

    cout << "Sorted array: ";
    for (const auto &item : A)
    {
        cout << item << " ";
    }
    cout << endl;
}

int main()
{
    testQuickSort();
    return 0;
}