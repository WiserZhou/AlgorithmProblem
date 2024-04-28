class DisjointSet:
    def __init__(self):
        self.parent = {}
        self.rank = {}

    def make_set(self, vertex):
        """
        创建一个新集合，只包含vertex。
        """
        self.parent[vertex] = vertex
        self.rank[vertex] = 0

    def find_set(self, vertex):
        """
        查找vertex所属的集合的代表元素（根节点）。
        使用路径压缩优化。
        """
        if self.parent[vertex] != vertex:
            self.parent[vertex] = self.find_set(self.parent[vertex])
        return self.parent[vertex]

    def union(self, u, v):
        """
        合并包含u和v的两个集合。
        使用按秩合并优化。
        """
        root_u = self.find_set(u)
        root_v = self.find_set(v)

        if root_u != root_v:
            if self.rank[root_u] > self.rank[root_v]:
                self.parent[root_v] = root_u
            elif self.rank[root_u] < self.rank[root_v]:
                self.parent[root_u] = root_v
            else:
                self.parent[root_v] = root_u
                self.rank[root_u] += 1
