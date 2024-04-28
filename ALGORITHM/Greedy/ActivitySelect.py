from typing import List, Tuple


# 定义活动类
class Activity:
    def __init__(self, start: int, finish: int):
        self.start = start
        self.finish = finish


# 贪心算法实现最大相容活动选择
def greedy_activity_selector(activities: List[Activity]) -> List[int]:
    # 首先按照活动的结束时间对活动进行排序
    sorted_activities = sorted(activities, key=lambda a: a.finish)

    # 初始化结果集合，包含第一个活动（索引从0开始）
    selected_activities = [0]

    # 初始化当前选择活动的结束时间
    current_finish_time = sorted_activities[0].finish

    # 遍历活动列表，选择相容的活动
    for i in range(1, len(sorted_activities)):
        if sorted_activities[i].start >= current_finish_time:
            # 如果当前活动的开始时间大于等于已选活动的结束时间，则选择该活动
            selected_activities.append(i)
            current_finish_time = sorted_activities[i].finish

    return selected_activities


# 示例活动集合
activities = [Activity(1, 4), Activity(3, 5), Activity(0, 6), Activity(5, 7), Activity(8, 9), Activity(5, 9)]
selected_activities = greedy_activity_selector(activities)

print("Selected activities: ", end="")
for index in selected_activities:
    print(f"({activities[index].start}, {activities[index].finish}) ", end="")
print()
