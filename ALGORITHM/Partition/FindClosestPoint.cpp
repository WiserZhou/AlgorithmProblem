#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 定义一个表示点的结构体
struct Point
{
    double x, y;
};

// 计算两点之间的欧氏距离
double distance(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// 使用分治法查找二维平面上一组点中的最近点对
pair<Point, Point> findClosestPair(vector<Point> &X, vector<Point> &Y)
{
    // 边界条件：如果点的数量小于等于3，则可以直接计算所有点对的距离并返回最近的一对
    if (X.size() <= 3)
    {
        double minDist = numeric_limits<double>::max();
        pair<Point, Point> closestPair;
        for (size_t i = 0; i < X.size(); ++i)
        {
            for (size_t j = i + 1; j < X.size(); ++j)
            {
                double dist = distance(X[i], Y[j]);
                if (dist < minDist)
                {
                    minDist = dist;
                    closestPair = make_pair(X[i], Y[j]);
                }
            }
        }
        return closestPair;
    }

    // Divide（分解）：按照x坐标对点进行排序，并找到中位数m作为分割线
    sort(X.begin(), X.end(), [](const Point &a, const Point &b)
         { return a.x < b.x; });
    size_t mid = X.size() / 2;
    double m = X[mid].x;

    // 根据分割线m将点集划分为左右两部分
    vector<Point> XL(X.begin(), X.begin() + mid);
    vector<Point> XR(X.begin() + mid, X.end());

    // 对应的y坐标也进行相应的分割
    vector<Point> YL(Y.begin(), Y.begin() + mid);
    vector<Point> YR(Y.begin() + mid, Y.end());

    // Conquer（征服）：递归地在左右子集中寻找最近点对
    pair<Point, Point> closestPairL = findClosestPair(XL, YL);
    pair<Point, Point> closestPairR = findClosestPair(XR, YR);

    // 更新全局最小距离
    double minDist = min(distance(closestPairL.first, closestPairL.second),
                         distance(closestPairR.first, closestPairR.second));

    // Merge（合并）：检查分割线附近的点对以找到可能的更近点对
    // 注意：此处根据简化后的伪代码实现，实际解决二维最近点对问题时需要采用更精确的方法
    vector<Point> ZL, ZR;
    // 假设临界区为距离分割线m不超过minDist的点
    for (size_t i = 0; i < mid && X[i].x <= m + minDist; ++i)
        ZL.push_back(X[i]);

    for (size_t i = X.size() - 1; i >= mid && X[i].x >= m - minDist; --i)
        ZR.push_back(X[i]);

    // 搜索临界区内的点对
    for (const auto &p : ZL)
    {
        for (const auto &q : ZR)
        {
            if (distance(p, q) < minDist)
            {
                minDist = distance(p, q);
                closestPairL = make_pair(p, q);
            }
        }
    }

    // 返回全局最近点对，这里假设closestPairL已更新为全局最近点对
    return closestPairL;
}

int main()
{
    // 测试函数，使用一些示例点进行测试
    return 0;
}