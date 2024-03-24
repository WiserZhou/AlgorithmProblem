#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定义一个计数排序函数
void countingSort(vector<int> &arr, int exp)
{
    int n = arr.size();
    vector<int> output(n);
    vector<int> count(10, 0); // 0到9，共10个数字

    // 统计每个数字出现的次数
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // 将count数组中的值修改为对应的输出位置
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // 根据count数组中的值将元素放到正确的位置上
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 将排序好的数组赋值给原数组
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// 定义Radix Sort函数
void radixSort(vector<int> &arr)
{
    int max_element_value = *max_element(arr.begin(), arr.end()); // 找到数组中最大的元素,max_element获取的是指向位置的迭代器

    // 对每一位进行计数排序
    for (int exp = 1; max_element_value / exp > 0; exp *= 10)
        countingSort(arr, exp);
}

int main()
{
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    cout << "Original Array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    radixSort(arr);

    cout << "Sorted Array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    return 0;
}
