#include <iostream>
#include <vector>
#include <algorithm>

struct Point
{
    int x;
    int y;
};

bool comparePoints(const Point &p1, const Point &p2)
{
    if (p1.x == p2.x)
        return p1.y < p2.y;
    return p1.x < p2.x;
}

std::vector<Point> SKL(const std::vector<Point> &D)
{
    std::vector<Point> S;

    if (D.size() < 3)
        return S;

    Point p = D[D.size() / 2];

    std::vector<Point> DL, DR;

    for (const auto &q : D)
    {
        if (comparePoints(q, p))
            DL.push_back(q);
        else if (comparePoints(p, q))
            DR.push_back(q);
    }

    if (DL.size() < D.size() / 2)
    {
        for (size_t j = 0; j < D.size() / 2 - DL.size(); ++j)
        {
            DL.push_back({p.x, p.y});
        }
    }

    if (DR.size() < (D.size() + 1) / 2)
    {
        for (size_t j = 0; j < (D.size() + 1) / 2 - DR.size(); ++j)
        {
            DR.push_back({p.x, p.y});
        }
    }

    std::vector<Point> SL = SKL(DL);
    std::vector<Point> SR = SKL(DR);

    int y1 = std::numeric_limits<int>::min();
    int y2 = std::numeric_limits<int>::min();

    for (const auto &q : SR)
    {
        if (q.x == p.x && q.y > y1)
            y1 = q.y;
        else if (q.x > p.x && q.y > y2)
            y2 = q.y;
    }

    for (const auto &q : SL)
    {
        if (q.x == p.x && q.y == y1 && q.y > y2)
            S.push_back(q);
        else if (q.x < p.x && q.y > y1 && q.y > y2)
            S.push_back(q);
    }

    return S;
}

int main()
{
    // Sample usage
    std::vector<Point> D = {{1, 5}, {2, 7}, {3, 6}, {4, 10}, {5, 8}, {6, 3}, {7, 4}};
    std::vector<Point> skyline = SKL(D);

    std::cout << "Skyline points: ";
    for (const auto &p : skyline)
    {
        std::cout << "(" << p.x << ", " << p.y << ") ";
    }
    std::cout << std::endl;

    return 0;
}
