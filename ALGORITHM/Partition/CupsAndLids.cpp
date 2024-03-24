#include <iostream>
#include <vector>
using namespace std;

// 函数用于匹配杯子和杯盖
// 返回值为匹配结果：0表示杯子太大，1表示匹配成功，2表示杯盖太大
int matchCupAndCover(int cupSize, int coverSize)
{
    if (cupSize == coverSize)
        return 1; // 匹配成功
    else if (cupSize < coverSize)
        return 0; // 杯子太大
    else
        return 2; // 杯盖太大
}

// 分治算法的主要函数
// 参数说明：cups为杯子大小的数组，covers为杯盖大小的数组，start和end表示当前处理的范围
void matchAndSort(vector<int> &cups, vector<int> &covers, int start, int end)
{
    // 边界条件：只剩下一个杯子和一个杯盖时，直接尝试匹配
    if (start >= end)
    {
        int result = matchCupAndCover(cups[start], covers[start]);
        if (result == 0)
            cout << "Cup is too big for cover." << endl;
        else if (result == 1)
            cout << "Matched." << endl;
        else
            cout << "Cover is too big for cup." << endl;
        return;
    }

    // 找到杯子和杯盖的中间位置
    int mid = (start + end) / 2;

    // 匹配较小的杯子和较小的杯盖
    matchAndSort(cups, covers, start, mid);
    // 匹配较大的杯子和较大的杯盖
    matchAndSort(cups, covers, mid + 1, end);

    // 排序并匹配
    int left = start;
    int right = mid + 1;
    vector<int> tempCups, tempCovers;
    while (left <= mid && right <= end)
    {
        if (cups[left] <= covers[right])
        {
            tempCups.push_back(cups[left]);
            tempCovers.push_back(covers[left]);
            left++;
        }
        else
        {
            tempCups.push_back(cups[right]);
            tempCovers.push_back(covers[right]);
            right++;
        }
    }
    while (left <= mid)
    {
        tempCups.push_back(cups[left]);
        tempCovers.push_back(covers[left]);
        left++;
    }
    while (right <= end)
    {
        tempCups.push_back(cups[right]);
        tempCovers.push_back(covers[right]);
        right++;
    }

    // 更新原始数组
    for (int i = start; i <= end; ++i)
    {
        cups[i] = tempCups[i - start];
        covers[i] = tempCovers[i - start];
    }
}

int main()
{
    // 示例输入：杯子大小和杯盖大小
    vector<int> cups = {3, 2, 5, 1, 4};
    vector<int> covers = {1, 2, 3, 4, 5};

    // 调用分治算法进行匹配并排序
    matchAndSort(cups, covers, 0, cups.size() - 1);

    // 输出排序后的杯子和杯盖
    cout << "Sorted cups: ";
    for (int cup : cups)
    {
        cout << cup << " ";
    }
    cout << endl;

    cout << "Sorted covers: ";
    for (int cover : covers)
    {
        cout << cover << " ";
    }
    cout << endl;

    return 0;
}
