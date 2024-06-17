#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <stack>

using namespace std;

// 物品结构体
struct Item
{
    int weight;
    int value;
    double ratio;
};

// 节点结构体
struct Node
{
    int level;
    int profit;
    int weight;
    double bound;
};

// 比较函数用于按价值重量比排序
bool compareRatio(const Item &a, const Item &b)
{
    return a.ratio > b.ratio;
}

// 计算节点的上界
double bound(Node u, int n, int W, vector<Item> &items)
{
    if (u.weight >= W)
    {
        return 0;
    }
    double profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;

    while (j < n && totweight + items[j].weight <= W)
    {
        totweight += items[j].weight;
        profit_bound += items[j].value;
        j++;
    }

    if (j < n)
    {
        profit_bound += (W - totweight) * items[j].ratio;
    }

    return profit_bound;
}

// 爬山法实现0/1背包问题
void knapsack(int W, vector<Item> &items, int n)
{
    sort(items.begin(), items.end(), compareRatio);

    stack<Node> S;
    Node u, v;

    u.level = -1;
    u.profit = u.weight = 0;
    S.push(u);

    int maxProfit = 0;

    while (!S.empty())
    {
        u = S.top();
        S.pop();

        if (u.level == -1)
        {
            v.level = 0;
        }

        if (u.level == n - 1)
        {
            continue;
        }

        v.level = u.level + 1;

        // 向左分支，即选择当前物品
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;

        if (v.weight <= W && v.profit > maxProfit)
        {
            maxProfit = v.profit;
        }

        v.bound = bound(v, n, W, items);

        if (v.bound > maxProfit)
        {
            S.push(v);
        }

        // 向右分支，即不选择当前物品
        v.weight = u.weight;
        v.profit = u.profit;

        v.bound = bound(v, n, W, items);

        if (v.bound > maxProfit)
        {
            S.push(v);
        }
    }

    cout << "Maximum profit: " << maxProfit << endl;
}

int main()
{
    int n, W;
    cout << "输入物品数量: ";
    cin >> n;
    cout << "输入背包承重: ";
    cin >> W;

    vector<Item> items(n);
    cout << "输入物品的重量和价值: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "物品 " << i + 1 << " : ";
        cin >> items[i].weight >> items[i].value;
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    knapsack(W, items, n);

    return 0;
}
