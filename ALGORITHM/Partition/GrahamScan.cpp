#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> // 包含 cmath 头文件以使用 atan2 函数

using namespace std;

// 定义二维点的结构体
struct Point
{
    int x, y;
};

// 比较函数，用于按照极角大小排序
bool compare(const Point &p1, const Point &p2)
{
    // 计算两点相对于原点的极角
    double angle1 = atan2(p1.y, p1.x);
    double angle2 = atan2(p2.y, p2.x);
    // 按照极角大小进行排序
    return angle1 < angle2;
}

// 返回两点构成的向量的叉积
int crossProduct(const Point &p0, const Point &p1, const Point &p2)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

// Graham Scan 算法
vector<Point> grahamScan(vector<Point> &Q)
{
    int n = Q.size();
    vector<Point> S; // 栈
    // 找到 y-坐标值最小的点 p0
    Point p0 = Q[0];
    for (int i = 1; i < n; ++i)
    {
        if (Q[i].y < p0.y || (Q[i].y == p0.y && Q[i].x < p0.x))
        {
            p0 = Q[i];
        }
    }
    // 将 p0 移动到 Q 的开头
    swap(Q[0], p0);
    // 按照与 p0 极角大小排序 Q 中其余点
    sort(Q.begin() + 1, Q.end(), compare);
    // 将 p0, p1, p2 入栈
    S.push_back(Q[0]);
    S.push_back(Q[1]);
    S.push_back(Q[2]);
    // 开始进行扫描
    for (int i = 3; i < n; ++i)
    {
        // 逆时针方向形成非左移动，即叉积大于等于0
        while (crossProduct(S[S.size() - 2], S.back(), Q[i]) < 0)
        {
            S.pop_back(); // 栈顶元素出栈
        }
        S.push_back(Q[i]); // 当前点入栈
    }
    return S;
}

int main()
{
    // 示例输入
    vector<Point> Q = {{1, 1}, {2, 3}, {4, 2}, {3, 5}, {5, 4}, {6, 1}, {7, 3}, {8, 2}, {9, 5}, {10, 4}};
    vector<Point> convexHull;
    if (Q.size() < 3)
    {
        return -1;
    }
    else if (Q.size() == 3)
    {
        convexHull = Q;
    }
    else
    {
        // 执行 Graham Scan 算法
        convexHull = grahamScan(Q);
    }
    // 输出凸包的顶点坐标
    cout << "Convex Hull points:\n";
    for (Point p : convexHull)
    {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}
