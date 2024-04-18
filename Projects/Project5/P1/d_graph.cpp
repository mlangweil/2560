#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
using namespace std;

typedef pair<int, int> Pair;

class Edge
{
public:
    int src, dest, weight;
    string direction;
    bool operator<(const Edge &other) const
    {
        // Compare src, dest, and direction
        if (src != other.src)
            return src < other.src;
        if (dest != other.dest)
            return dest < other.dest;
        return direction < other.direction;
    }
};

class Graph
{
public:
    // a vector of vectors of Pairs to represent an adjacency list
    map<int, vector<Edge>> adjList;
    Graph() {}
    void createGraph(vector<Edge> edges)
    {
        for (Edge edge : edges)
        {
            adjList[edge.src].push_back(edge);
        }
    };

    void printGraph()
    {
        for (const auto &node : adjList)
        {
            int src = node.first;
            const vector<Edge> &edges = node.second;

            cout << "Node " << src << " has edges to: ";
            for (const Edge &edge : edges)
            {
                if (edge.src == src)
                {
                    cout << edge.dest << " (Weight: " << edge.weight << ", " << edge.direction << "), ";
                }
            }
            cout << endl;
        }
    }

    void findPathNonRecursive(int currNode, int targetNode)
    {
        stack<int> stack;
        vector<int> visited; // Use a vector to store visited nodes

        stack.push(currNode); // Push the starting node onto the stack

        while (!stack.empty())
        {
            currNode = stack.top();
            stack.pop();

            visited.push_back(currNode); // Mark current node as visited

            if (currNode == targetNode)
            {
                cout << "Path found" << endl;
                return;
            }

            // Iterate through neighbors of current node
            for (auto edge : adjList[currNode])
            {
                if (find(visited.begin(), visited.end(), edge.dest) == visited.end())
                {
                    stack.push(edge.dest);
                    cout << edge.direction << " ";
                }
            }
        }

        cout << "No path exists" << endl;
    }

    bool findPathRecursive(int currNode, int targetNode, vector<int> &visited, stack<int> &stack)
    {

        currNode = stack.top();
        stack.pop();

        visited.push_back(currNode); // Mark current node as visited
        // Iterate through neighbors of current node
        for (auto edge : adjList[currNode])
        {
            if (find(visited.begin(), visited.end(), edge.dest) == visited.end())
            {
                stack.push(edge.dest);
                cout << edge.direction << " ";
            }
        }
        if (currNode == targetNode)
        {
            cout << "Path found" << endl;
            return true;
        }
        if (!stack.empty())
        {
            return findPathRecursive(currNode, targetNode, visited, stack);
        }
        else if (stack.empty())
        {
            cout << "No path exists" << endl;
            return false;
        }
    }
};
