#include <iostream>
#include <vector>
#include <string>

// 表示析取式的类型
using Clause = std::vector<int>;

// 打印布尔变量的赋值
void printSolution(const std::vector<bool> &assignment)
{
    for (bool val : assignment)
    {
        std::cout << (val ? "True " : "False ");
    }
    std::cout << std::endl;
}

// 检查当前赋值是否满足所有的析取式
bool isSatisfied(const std::vector<Clause> &clauses, const std::vector<bool> &assignment)
{
    for (const Clause &clause : clauses)
    {
        bool clauseSatisfied = false;
        for (int literal : clause)
        {
            if (literal > 0 && assignment[literal - 1])
            {
                clauseSatisfied = true;
                break;
            }
            else if (literal < 0 && !assignment[-literal - 1])
            {
                clauseSatisfied = true;
                break;
            }
        }
        if (!clauseSatisfied)
        {
            return false;
        }
    }
    return true;
}

// 递归搜索赋值
bool solveSAT(const std::vector<Clause> &clauses, std::vector<bool> &assignment, int index)
{
    if (index == assignment.size())
    {
        return isSatisfied(clauses, assignment);
    }

    // 尝试赋值为False
    assignment[index] = false;
    if (solveSAT(clauses, assignment, index + 1))
    {
        return true;
    }

    // 尝试赋值为True
    assignment[index] = true;
    if (solveSAT(clauses, assignment, index + 1))
    {
        return true;
    }

    return false;
}

int main()
{
    // 输入布尔变量的数量
    int n;
    std::cout << "输入布尔变量的数量: ";
    std::cin >> n;

    // 输入析取式的数量
    int k;
    std::cout << "输入析取式的数量: ";
    std::cin >> k;

    // 输入每个析取式
    std::vector<Clause> clauses(k);
    std::cout << "输入每个析取式 (例如: 1 -2 3 表示 x1 OR NOT x2 OR x3, 输入0结束该析取式):\n";
    for (int i = 0; i < k; ++i)
    {
        std::cout << "析取式 " << i + 1 << ": ";
        int literal;
        while (std::cin >> literal && literal != 0)
        {
            clauses[i].push_back(literal);
        }
    }

    // 初始化布尔变量的赋值
    std::vector<bool> assignment(n, false);

    // 尝试找到一个解
    if (solveSAT(clauses, assignment, 0))
    {
        std::cout << "存在一种赋值使得所有析取式皆为真:\n";
        printSolution(assignment);
    }
    else
    {
        std::cout << "不存在一种赋值使得所有析取式皆为真.\n";
    }

    return 0;
}
