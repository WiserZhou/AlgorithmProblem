#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定义边的结构体
struct Edge
{
    int u, v, weight;
};

// 定义并查集
class DisjointSet
{
private:
    vector<int> parent, rank;

public:
    DisjointSet(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        // 初始化每个元素的父节点为自身
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // 查找元素所属的集合（根节点）
    int find(int u)
    {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // 合并两个集合
    void merge(int u, int v)
    {
        int pu = find(u), pv = find(v);
        if (pu != pv)
        {
            if (rank[pu] < rank[pv])
                swap(pu, pv); // 如果pv更深，那么将pv和pu的值互换
            parent[pv] = pu;  // pu是最深的那个
            if (rank[pu] == rank[pv])
                rank[pu]++; // 如果相等，那么pu的深度增加
        }
    }
};

// Kruskal算法
vector<Edge> kruskal(vector<Edge> &edges, int V)
{
    vector<Edge> MST;
    // 按边的权重升序排序
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
         { return a.weight < b.weight; });

    DisjointSet ds(V);

    for (const auto &edge : edges)
    {
        int u = edge.u, v = edge.v, weight = edge.weight;
        if (ds.find(u) != ds.find(v))
        {
            MST.push_back({u, v, weight});
            ds.merge(u, v);
        }
    }

    return MST;
}

int main()
{
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);
    cout << "Enter edges in the format (u v weight):" << endl;
    for (int i = 0; i < E; ++i)
    {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    vector<Edge> MST = kruskal(edges, V);

    cout << "Minimum Spanning Tree:" << endl;
    for (const auto &edge : MST)
    {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }

    return 0;
}
