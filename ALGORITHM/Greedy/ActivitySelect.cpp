#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定义活动结构体
struct Activity
{
    int start;
    int finish;
};

// 贪心算法实现最大相容活动选择
vector<int> GreedyActivitySelector(const vector<Activity> &activities)
{
    // 首先按照活动的结束时间对活动进行排序
    vector<Activity> sorted_activities = activities;
    sort(sorted_activities.begin(), sorted_activities.end(), [](const Activity &a, const Activity &b)
         { return a.finish < b.finish; });

    // 初始化结果集合，包含第一个活动
    vector<int> selected_activities;
    selected_activities.push_back(0);

    // 初始化当前选择活动的结束时间
    int current_finish_time = sorted_activities[0].finish;

    // 遍历活动列表，选择相容的活动
    for (size_t i = 1; i < sorted_activities.size(); ++i)
    {
        if (sorted_activities[i].start >= current_finish_time)
        {
            // 如果当前活动的开始时间大于等于已选活动的结束时间，则选择该活动
            selected_activities.push_back(i);
            current_finish_time = sorted_activities[i].finish;
        }
    }

    return selected_activities;
}

int main()
{
    // 示例活动集合
    vector<Activity> activities = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};
    vector<int> selected_activities = GreedyActivitySelector(activities);

    cout << "Selected activities: ";
    for (int index : selected_activities)
    {
        cout << "(" << activities[index].start << ", " << activities[index].finish << ") ";
    }
    cout << endl;

    return 0;
}