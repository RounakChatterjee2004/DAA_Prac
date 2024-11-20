#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;

int TSPUtil(vector<vector<int>> &graph, vector<bool> &visited, int currPos, int n, int count, int cost)
{
    if (count == n && graph[currPos][0] > 0)
    {
        return cost + graph[currPos][0];
    }

    int minCost = INF;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && graph[currPos][i] > 0)
        {
            visited[i] = true;
            int tempCost = TSPUtil(graph, visited, i, n, count + 1, cost + graph[currPos][i]);
            minCost = min(minCost, tempCost);
            visited[i] = false; // backtrack
        }
    }
    return minCost;
}

int TSPBranchBound(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    visited[0] = true; // mark first city visited
    return TSPUtil(graph, visited, 0, n, 1, 0);
}

int main()
{
    vector<vector<int>> graph = {
        {0, 10, 15, 20},
        {5, 0, 9, 10},
        {6, 13, 0, 12},
        {8, 8, 9, 0},
    };

    int result = TSPBranchBound(graph);
    cout << "The total minimum cost extracted from this algorithm is : " << result << endl;
    return 0;
}
