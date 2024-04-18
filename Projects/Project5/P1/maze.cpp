
// Project 5
#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "d_graph.cpp"
#include <chrono>
#include <iomanip> // for setw

using namespace std;
class maze
{
public:
    maze(ifstream &fin);
    void print(int, int, int, int);
    bool isLegal(int i, int j);
    void setMap(int i, int j, int n);
    int getMap(int i, int j) const;
    void mapMazeToGraph();
    void initMap();
    void printMap();
    int rows; // number of rows in the maze
    int cols; // number of columns in the maze
    void findPathRecursive(int goalI, int goalJ, int currI, int currJ);
    void findPathNonRecursive(int goalI, int goalJ, int currI, int currJ);
    void printGraph();

private:
    matrix<bool> value;
    matrix<int> map; // Mapping from maze (i,j) values to node
    Graph g;
};

void maze::printGraph()
{
    g.printGraph();
}

int generateRandomNumber()
{
    return (rand() % 4) + 1;
}

void maze::initMap()
{
    int n = 1;
    for (int i = 0; i <= rows - 1; i++)
    {
        for (int j = 0; j <= cols - 1; j++)
        {
            if (value[i][j])
            {
                // cout << "(" << i << "," << j << ")" << " node: " << n << endl;
                setMap(i, j, n);
            }
            n++;
        }
    }
}

void maze::setMap(int i, int j, int n)
{
    if (i < 0 || i > rows || j < 0 || j > cols)
        throw rangeError("Bad value in maze::isLegal");
    map[i][j] = n;
}
int maze ::getMap(int i, int j) const
{
    if (i < 0 || i > rows || j < 0 || j > cols)
        throw rangeError("Bad value in maze::isLegal");
    return map[i][j];
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin. Assumes that the
// number of rows and columns indicated in the file are correct.
{
    fin >> rows;
    fin >> cols;
    char x;
    value.resize(rows, cols);
    for (int i = 0; i <= rows - 1; i++)
        for (int j = 0; j <= cols - 1; j++)
        {
            fin >> x;
            if (x == 'O')
                value[i][j] = true;
            else
                value[i][j] = false;
        }
    map.resize(rows, cols);
    // initMap();
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
    cout << endl;
    if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
        throw rangeError("Bad value in maze::print");
    if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
        throw rangeError("Bad value in maze::print");
    for (int i = 0; i <= rows - 1; i++)
    {
        for (int j = 0; j <= cols - 1; j++)
        {
            if (i == goalI && j == goalJ)
                cout << "*";
            else if (i == currI && j == currJ)
                cout << "+";
            else if (value[i][j])
                cout << " ";
            else
                cout << "X";
        }
        cout << endl;
    }
    cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze.
{
    if (i < 0 || i > rows || j < 0 || j > cols)
        throw rangeError("Bad value in maze::isLegal");
    return value[i][j];
}

void maze::mapMazeToGraph()
{
    initMap();
    vector<Edge> edges;

    // Get the starting node
    int startNode = getMap(0, 0);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int currentNode = getMap(i, j);

            if (currentNode != 0) // Skip non-existent nodes
            {
                if (i > 0 && isLegal(i - 1, j))
                {
                    int neighborNode = getMap(i - 1, j);
                    Edge edge;
                    edge.weight = 0;
                    edge.src = currentNode;
                    edge.dest = neighborNode;
                    edge.direction = "UP";
                    edges.push_back(edge);
                }
                if (j > 0 && isLegal(i, j - 1))
                {
                    int neighborNode = getMap(i, j - 1);
                    Edge edge;
                    edge.weight = 0;
                    edge.src = currentNode;
                    edge.dest = neighborNode;
                    edge.direction = "LEFT";
                    edges.push_back(edge);
                }
            }
        }
    }

    vector<Edge> newEdges;
    srand((unsigned)time(NULL));

    // duplicates edges and makes it an undirected graph by making it two way directed and assign random weights
    for (Edge &node : edges)
    {
        int num = generateRandomNumber();
        Edge edge;
        edge.src = node.dest;
        edge.dest = node.src;
        edge.weight = num;
        node.weight = num;

        // Set direction for the original edge
        if (node.direction == "UP")
        {
            edge.direction = "DOWN";
        }
        else if (node.direction == "LEFT")
        {
            edge.direction = "RIGHT";
        }

        newEdges.push_back(node);
        newEdges.push_back(edge);
    }

    g.createGraph(newEdges);
    g.printGraph();
}

void maze::printMap()
{
    for (int i = 0; i <= rows - 1; i++)
    {
        for (int j = 0; j <= cols - 1; j++)
        {
            cout << setw(3) << map[i][j] << " ";
        }
        cout << endl;
    }
}

void maze::findPathNonRecursive(int goalI, int goalJ, int currI, int currJ)
{
    int currNode = getMap(currI, currJ);
    int targetNode = getMap(goalI, goalJ);
    g.findPathNonRecursive(currNode, targetNode);
}

void maze::findPathRecursive(int goalI, int goalJ, int currI, int currJ)
{
    int currNode = getMap(currI, currJ);
    int targetNode = getMap(goalI, goalJ);
    vector<int> visited;
    stack<int> stack;
    stack.push(currNode);
    g.findPathRecursive(currNode, targetNode, visited, stack);
}

int main()
{

    char x;
    ifstream fin;
    // Read the maze from the file.
    string fileName = "maze3-1.txt";
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
    try
    {

        while (fin && fin.peek() != 'Z')
        {
            maze m(fin);
            m.print(0, 0, 19, 19);
            m.printMap();
            m.mapMazeToGraph();
            m.findPathNonRecursive(0, 0, 19, 19);
            m.findPathRecursive(0, 0, 19, 19);
        }
    }
    catch (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
    catch (rangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
}
