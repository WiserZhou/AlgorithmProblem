#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// 目标状态
const vector<vector<int>> goalState = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}};

// 用于表示棋盘状态的类
class PuzzleState
{
public:
    vector<vector<int>> board;
    int x, y; // 空格的位置

    PuzzleState(vector<vector<int>> b)
    {
        board = b;
        // 找到空格的位置
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board[i][j] == 0)
                {
                    x = i;
                    y = j;
                    return;
                }
            }
        }
    }

    // 计算启发式函数值（曼哈顿距离）
    int heuristic() const
    {
        int dist = 0;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board[i][j] != 0)
                {
                    int val = board[i][j];
                    int targetX = (val - 1) / 3;
                    int targetY = (val - 1) % 3;
                    dist += abs(i - targetX) + abs(j - targetY);
                }
            }
        }
        return dist;
    }

    // 检查当前状态是否是目标状态
    bool isGoal() const
    {
        return board == goalState;
    }

    // 生成子状态
    vector<PuzzleState> generateChildren() const
    {
        vector<PuzzleState> children;
        vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 上下左右

        for (const auto &move : moves)
        {
            int newX = x + move.first;
            int newY = y + move.second;
            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3)
            {
                vector<vector<int>> newBoard = board;
                swap(newBoard[x][y], newBoard[newX][newY]);
                children.push_back(PuzzleState(newBoard));
            }
        }

        return children;
    }

    // 打印当前状态
    void print() const
    {
        for (const auto &row : board)
        {
            for (int val : row)
            {
                cout << val << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

// 比较函数用于按启发式函数值排序
bool compareHeuristic(const PuzzleState &a, const PuzzleState &b)
{
    return a.heuristic() > b.heuristic();
}

void hillClimbing(PuzzleState initialState)
{
    stack<PuzzleState> S;
    S.push(initialState);

    while (!S.empty())
    {
        PuzzleState current = S.top();
        if (current.isGoal())
        {
            cout << "找到目标状态:" << endl;
            current.print();
            return;
        }

        S.pop();
        vector<PuzzleState> children = current.generateChildren();
        sort(children.begin(), children.end(), compareHeuristic);

        for (const auto &child : children)
        {
            S.push(child);
        }
    }

    cout << "未能找到解决方案." << endl;
}

int main()
{
    vector<vector<int>> initialState = {
        {2, 8, 3},
        {1, 6, 4},
        {7, 0, 5}};

    PuzzleState initial(initialState);
    cout << "初始状态:" << endl;
    initial.print();

    hillClimbing(initial);

    return 0;
}
