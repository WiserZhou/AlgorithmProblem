#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>

using namespace std;

const vector<vector<int>> goalState = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}};

class PuzzleState
{
public:
    vector<vector<int>> board;
    int x, y; // 空格的位置

    PuzzleState(vector<vector<int>> b)
    {
        board = b;
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

    bool isGoal() const
    {
        return board == goalState;
    }

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

    bool operator==(const PuzzleState &other) const
    {
        return board == other.board;
    }
};

// 用于比较PuzzleState的优先级队列
struct CompareHeuristic
{
    bool operator()(const PuzzleState &a, const PuzzleState &b)
    {
        return a.heuristic() > b.heuristic();
    }
};

string boardToString(const vector<vector<int>> &board)
{
    string str;
    for (const auto &row : board)
    {
        for (int val : row)
        {
            str += to_string(val) + ",";
        }
    }
    return str;
}

void bestFirstSearch(PuzzleState initialState)
{
    priority_queue<PuzzleState, vector<PuzzleState>, CompareHeuristic> H;
    unordered_set<string> visited;
    H.push(initialState);
    visited.insert(boardToString(initialState.board));

    while (!H.empty())
    {
        PuzzleState current = H.top();
        H.pop();

        if (current.isGoal())
        {
            cout << "找到目标状态:" << endl;
            current.print();
            return;
        }

        vector<PuzzleState> children = current.generateChildren();
        for (const auto &child : children)
        {
            string childBoardStr = boardToString(child.board);
            if (visited.find(childBoardStr) == visited.end())
            {
                H.push(child);
                visited.insert(childBoardStr);
            }
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

    bestFirstSearch(initial);

    return 0;
}
