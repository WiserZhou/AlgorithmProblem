// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;
// bool cmp(const pair<int, int> &a, const pair<int, int> &b)
// {
//     return a.first < b.first;
// }

// void Greedy(vector<pair<int, int>> &L)
// {
//     sort(L.begin(), L.end(), cmp);
// }

// void print(const vector<pair<int, int>> &L)
// {
//     int n = L.size();
//     for (int i = 0; i < n; i++)
//     {
//         cout << L[i].second << " ";
//     }
// }
// int main()
// {
//     vector<pair<int, int>> L;
//     // input
//     Greedy(L);
//     print(L);
//     return 0;
// }

#include <iostream>
#include <vector>
#include <algorithm>

// 结构体用于表示输入集合中的元素
struct Element
{
    int index; // 元素在输入集合中的索引
    int value; // 元素的值
};

// 自定义比较函数，用于元素按照值升序排序
bool compare(Element a, Element b)
{
    return a.value < b.value;
}

// 定义优化函数
std::vector<Element> optimal_plan(std::vector<Element> A, int threshold)
{
    std::vector<Element> result; // 用于存储优化后的结果
    std::vector<int> index_set;  // 用于存储索引集合

    // 初始化索引集合
    for (int i = 0; i < A.size(); ++i)
    {
        index_set.push_back(i);
    }

    // 循环直到索引集合为空
    while (!index_set.empty())
    {
        // 选择最小的元素
        Element min_element = *std::min_element(A.begin(), A.end(), compare);

        // 更新输出集合
        result.push_back(min_element);

        // 更新索引集合
        index_set.erase(std::remove(index_set.begin(), index_set.end(), min_element.index), index_set.end());

        // 遍历剩余元素
        for (int index : index_set)
        {
            // 计算差值
            int diff = A[index].value - min_element.value;

            // 更新元素值
            if (diff <= threshold)
            {
                A[index].value -= diff;
            }
            else
            {
                A[index].value -= threshold;
            }

            // 检查元素值
            if (A[index].value < 0)
            {
                A[index].value = 0;
            }
        }
    }

    // 排序输出集合
    std::sort(result.begin(), result.end(), compare);

    return result;
}

int main()
{
    // 输入集合A
    std::vector<Element> A = {{1, 5}, {2, 8}, {3, 3}, {4, 7}};
    // 预设值
    int threshold = 2;

    // 调用优化函数
    std::vector<Element> optimized_result = optimal_plan(A, threshold);

    // 输出结果
    for (Element elem : optimized_result)
    {
        std::cout << elem.value << " ";
    }

    return 0;
}
