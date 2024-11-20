#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

struct Node
{
    vector<vector<int>> costMatrix;
    int currentCost;
    vector<int> path;
    int level;

    Node()
    {
        currentCost = 0;
        level = 0;
    }
};

struct CompareCost
{
    bool operator()(Node const &a, Node const &b)
    {
        return a.currentCost > b.currentCost;
    }
};

vector<vector<int>> reduceMatrix(const vector<vector<int>> &mat, int &cost)
{
    int n = mat.size();
    vector<vector<int>> reducedMatrix = mat;

    // Row reduction
    for (int i = 0; i < n; i++)
    {
        int rowMin = INT_MAX;
        for (int j = 0; j < n; j++)
        {
            if (reducedMatrix[i][j] < rowMin)
            {
                rowMin = reducedMatrix[i][j];
            }
        }
        if (rowMin != INT_MAX)
        {
            cost += rowMin;
            for (int j = 0; j < n; j++)
            {
                if (reducedMatrix[i][j] != INT_MAX)
                {
                    reducedMatrix[i][j] -= rowMin;
                }
            }
        }
    }

    // Column reduction
    for (int j = 0; j < n; j++)
    {
        int colMin = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (reducedMatrix[i][j] < colMin)
            {
                colMin = reducedMatrix[i][j];
            }
        }
        if (colMin != INT_MAX)
        {
            cost += colMin;
            for (int i = 0; i < n; i++)
            {
                if (reducedMatrix[i][j] != INT_MAX)
                {
                    reducedMatrix[i][j] -= colMin;
                }
            }
        }
    }

    return reducedMatrix;
}

bool isLeafNode(const Node &node, int n)
{
    return node.level == n - 1;
}

vector<Node> getAllChildren(const Node &parent, const vector<vector<int>> &originalCostMatrix)
{
    vector<Node> children;
    int n = originalCostMatrix.size();
    int parentCity = parent.path.back();

    for (int nextCity = 0; nextCity < n; nextCity++)
    {
        if (find(parent.path.begin(), parent.path.end(), nextCity) == parent.path.end())
        {
            Node child;
            child.costMatrix = parent.costMatrix;

            for (int i = 0; i < n; i++)
            {
                child.costMatrix[i][nextCity] = INT_MAX;
                child.costMatrix[nextCity][i] = INT_MAX;
            }
            child.costMatrix[nextCity][0] = INT_MAX;

            child.currentCost = parent.currentCost + parent.costMatrix[parentCity][nextCity];
            int reductionCost = 0;
            child.costMatrix = reduceMatrix(child.costMatrix, reductionCost);
            child.currentCost += reductionCost;

            child.path = parent.path;
            child.path.push_back(nextCity);
            child.level = parent.level + 1;

            children.push_back(child);
        }
    }

    return children;
}

int solveTSP(const vector<vector<int>> &costMatrix)
{
    priority_queue<Node, vector<Node>, CompareCost> pq;
    int n = costMatrix.size();

    Node root;
    int rootReductionCost = 0;
    root.costMatrix = reduceMatrix(costMatrix, rootReductionCost);
    root.currentCost = rootReductionCost;
    root.level = 0;
    root.path.push_back(0);
    pq.push(root);

    int minCost = INT_MAX;

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();

        if (isLeafNode(current, n))
        {
            int totalCost = current.currentCost + current.costMatrix[current.path.back()][0];
            minCost = min(minCost, totalCost);
        }
        else
        {
            vector<Node> children = getAllChildren(current, costMatrix);
            for (Node &child : children)
            {
                pq.push(child);
            }
        }
    }

    return minCost;
}

int main()
{
    vector<vector<int>> costMatrix = {
        {INT_MAX, 11, 10, 9, 6},
        {8, INT_MAX, 7, 3, 4},
        {8, 4, INT_MAX, 4, 8},
        {11, 10, 5, INT_MAX, 5},
        {6, 9, 5, 5, INT_MAX}};

    cout << "Minimum cost derived is: " << solveTSP(costMatrix) << endl;
    return 0;
}
