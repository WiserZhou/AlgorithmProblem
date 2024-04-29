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
    vector<int> key(V, numeric_limits<int>::max()); // 所有顶点的键值初始化为无穷大，记录MST中与v节点相连的最短边的权重
    vector<int> pi(V, -1);                          // 父节点初始化为-1，记录MST中与v节点相连的最短边的顶点
    vector<bool> inMST(V, false);                   // 标记顶点是否在最小生成树中

    priority_queue<HeapNode, vector<HeapNode>, CompareHeapNode> minHeap; // 构建的最小堆

    key[root] = 0;
    minHeap.push({root, 0});

    while (!minHeap.empty())
    {
        int u = minHeap.top().vertex; // 把heap中权值最小的顶点加入进来
        minHeap.pop();
        inMST[u] = true;

        for (const Edge &edge : G[u]) // 对于所有与u连接的边
        {
            int v = edge.to; // v是边的另一端的终点
            int weight = edge.weight;
            if (!inMST[v] && weight < key[v]) // v不在MST中，且此边的权重比v的与MST中顶点的连接边的已记录的权重小，那么就替换
            {
                pi[v] = u;
                key[v] = weight;
                minHeap.push({v, key[v]}); // 把v和u，v边的权重加入heap中
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
