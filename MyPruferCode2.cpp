#include<iostream>
#include<vector>
#define NOTHING -1

// This function determines if x is father of y or vice versa
// It's hard to explain because it consists of many cases =)) (although it is my ideal)
bool Father(int x, int y, std::vector<int>& father)
{
    if (y == 0)
    {
        return Father(y, x, father);
    }

    if (father[y] == NOTHING)
    {
        father[y] = x;
        return true;
    }

    if (x == 0)
    {
        Father(y, father[y], father);
        father[y] = 0;
        return true;
    }
    else if (father[y] == 0)
    {
        if (father[x] != NOTHING && y != father[x])
        {
            Father(x, father[x], father);
        }
        father[x] = y;
        return false;
    }
    else if (Father(y, father[y], father))
    {
        father[y] = x;
        return true;
    }
    else
    {
        if (father[x] != NOTHING)
        {
            if (father[father[x]] == NOTHING)
            father[father[x]] = x;
        else if (father[x] != y)
            Father(x, father[x], father);
        }
        father[x] = y;
        return false;
    }

}


std::vector<int> CreatePruferCode(int numOfEdges, const std::vector<int>& father, std::vector<int>& deg)
{
    //Prufer code doesn't contain 0 at the end => only has E-1 elements
    std::vector<int> pruferCode(numOfEdges - 1);

    // Find the leaf that has smallest label (smallest leaf)
    int leaf = 1;
    while ( leaf < numOfEdges && deg[leaf] != 1) ++leaf;
    int lowestLeaf = leaf;

    for (int i = 0; i < numOfEdges - 1; ++i)
    {
        // Assign the adjacent vertex to connectVertex variable for reuseable
        int connectVertex = father[lowestLeaf];

        // The adjacent vertex is the next value of prufer code
        pruferCode[i] = connectVertex;

        // Decrease deg of smallest leaf and deg of adjacent vertex
        --deg[connectVertex];
        --deg[lowestLeaf];

        // If the adjacent vertex <> 0, deg = 1 and has label that is smaller than the smallest leaf => it is the next smallest leaf
        if (connectVertex != 0 && deg[connectVertex] == 1 && connectVertex < leaf)
        {
            lowestLeaf = connectVertex;
        }
        else // else, find the next smallest leaf 
        {
            while (leaf < numOfEdges && deg[leaf] != 1) ++leaf;
            lowestLeaf = leaf;
        }
    }
    return pruferCode;
}

int main()
{

    int numOfEdges;
    std::cin >> numOfEdges;

    // This array saves deg of each vertex, initialize = 0
    std::vector<int> deg(numOfEdges + 1, 0);
    // This array saves father of each vertex, initialize = NOTHING ( = -1)
    std::vector<int> father(numOfEdges + 1, NOTHING);

    // Read edges list, update deg array and father array
    int first, second;
    for (int i = 0; i < numOfEdges; ++i)
    {
        std::cin >> first >> second;
        ++deg[first];
        ++deg[second];

        Father(first, second, father);

    }

    std::vector<int> pruferCode = CreatePruferCode(numOfEdges, father, deg);

    /*std::vector<int> ans(numOfEdges);
    for (int i = 0; i < numOfEdges; ++i)
    {
        std::cin >> ans[i];
    }

    bool isCorrect = true;
    for (int i = 0; i < numOfEdges - 1; ++i)
    {
        if (ans[i] != pruferCode[i])
        {
            isCorrect = false;
            break;
        }
    }

    if (isCorrect)
        std::cout << "PASSED";
    else
        std::cout << "FAILED";*/
    

   
    // Print prufer code
   for (int i = 0; i < numOfEdges - 1; ++i)
   {
       std::cout << pruferCode[i] << ' ';
   }
    
    return 0;

}