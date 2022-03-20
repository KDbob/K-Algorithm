class Graph:
    # Constructor
    def __init__(self):
        self.graph = {
            "A": ["B", "C"],
            "B": ["A", "C", "D"],
            "C": ["A", "B", "D", "E"],
            "D": ["B", "C", "E", "F"],
            "E": ["C", "D"],
            "F": ["D"],
        }

    def BFS(self, v):
        queue = []  # ★利用数组模拟队列
        seen = set()  # seen集合用来标记已经加入的顶点
        queue.append(v)
        seen.add(v)
        while len(queue):
            vertex = queue.pop(0)
            print(vertex, end=' ')
            for i in self.graph[vertex]:
                if i not in seen:
                    queue.append(i)
                    seen.add(i)
        print("\n")

    def DFS(self, v):
        stack = []  # ★利用数组模拟栈
        seen = set()
        stack.append(v)
        seen.add(v)
        while len(stack):
            vertex = stack.pop()  # 栈的输出是"后进先出"
            print(vertex, end=' ')
            for i in self.graph[vertex]:
                if i not in seen:
                    stack.append(i)
                    seen.add(i)
        print("\n")

def DFS2(self, v):
    seen = set()
    def DFS_recur(vertex):
        seen.add(vertex)
        print(vertex, end=' ')
        for i in self.graph[vertex]:
            if i not in seen:
                DFS_recur(i)

    DFS_recur(v)
    print("\n")

# BFS的应用：最短路径
# 原理，每次判断相邻的节点的时候可以顺手保存一个parent字典
def BFS_shortest_path(self, v):
    queue = []
    seen = set()
    queue.append(v)
    seen.add(v)
    parent = {}
    while len(queue):
        vertex = queue.pop(0)
        # print(vertex)
        for i in self.graph[vertex]:
            if i not in seen:
                queue.append(i)
                seen.add(i)
                parent[i] = vertex  # 说明是i的前驱是vertex
    return parent


if __name__ == '__main__':
    g = Graph()
    g.BFS('A')  # expect: A B C D E F
    g.DFS('A')  # expect: A C E D F B
    g.DFS2('A')  # expect: A B C D E F
    # print(g.BFS_shortest_path('E'))
