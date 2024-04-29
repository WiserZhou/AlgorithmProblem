#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// 定义边的结构体
struct Edge
{
    int to, weight;
};

// 定义图的邻接表表示
typedef vector<vector<Edge>> Graph;

// 定义最小堆中的元素
struct HeapNode
{
    int vertex, key;
};

// 最小堆比较函数
struct CompareHeapNode
{
    bool operator()(const HeapNode &a, const HeapNode &b)
    {
        return a.key > b.key;
    }
};

// Prim算法
vector<Edge> prim(const Graph &G, int root)
{
    int V = G.size();
    vector<int> key(V, numeric_limits<int>::max()); // 所有顶点的键值初始化为无穷大
    vector<int> pi(V, -1);                          // 父节点初始化为-1
    vector<bool> inMST(V, false);                   // 标记顶点是否在最小生成树中

    priority_queue<HeapNode, vector<HeapNode>, CompareHeapNode> minHeap;

    key[root] = 0;
    minHeap.push({root, 0});

    while (!minHeap.empty())
    {
        int u = minHeap.top().vertex;
        minHeap.pop();
        inMST[u] = true;

        for (const Edge &edge : G[u])
        {
            int v = edge.to;
            int weight = edge.weight;
            if (!inMST[v] && weight < key[v])
            {
                pi[v] = u;
                key[v] = weight;
                minHeap.push({v, key[v]});
            }
        }
    }

    // 构造最小生成树的边集合
    vector<Edge> MST;
    for (int v = 0; v < V; ++v)
    {
        if (v != root)
        {
            MST.push_back({v, key[v]});
        }
    }

    return MST;
}

int main()
{
    int V, E, root;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;
    cout << "Enter the root vertex: ";
    cin >> root;

    Graph G(V);
    cout << "Enter edges in the format (to weight):" << endl;
    for (int i = 0; i < E; ++i)
    {
        int from, to, weight;
        cin >> from >> to >> weight;
        G[from].push_back({to, weight});
        G[to].push_back({from, weight}); // 无向图，双向都需要连接
    }

    vector<Edge> MST = prim(G, root);

    cout << "Minimum Spanning Tree:" << endl;
    for (const auto &edge : MST)
    {
        cout << edge.to << " - " << edge.weight << endl;
    }

    return 0;
}
