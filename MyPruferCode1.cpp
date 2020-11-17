#include<iostream>
#include<vector>
#include<list>

std::vector<int> CreatePruferCode(int numOfEdges, const std::vector<std::list<int>>& adjList, std::vector<int>& deg)
{
    //Prufer code doesn't contain 0 at the end => only has E-1 elements
    std::vector<int> pruferCode(numOfEdges - 1);

    // Find the leaf that has smallest label (smallest leaf)
    int leaf = 1;
    while ( leaf < numOfEdges && deg[leaf] != 1) ++leaf;
    int lowestLeaf = leaf;

    for (int i = 0; i < numOfEdges - 1; ++i)
    {
        // Find the adjacent vertex of smallest leaf, deg of which <> 0
        std::list<int>::const_iterator it = adjList[lowestLeaf].begin();
        for (; it != adjList[lowestLeaf].end() && deg[*it] == 0; ++it);
    
        // Assign the adjacent vertex to connectVertex variable for reuseable
        int connectVertex = *it;

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

    // Set up adjacent list, by using an array of linked list
    std::vector<std::list<int>> adjList(numOfEdges + 1);
    for (int i = 0; i < numOfEdges + 1; ++i)
    {
        adjList[i] = std::list<int>();
    }

    // Read edges list, update array of degree and adjacent list
    int first, second;
    for (int i = 0; i < numOfEdges; ++i)
    {
        std::cin >> first >> second;
        ++deg[first];
        ++deg[second];
        adjList[first].emplace_back(second);
        adjList[second].emplace_back(first);
    }

    std::vector<int> pruferCode = CreatePruferCode(numOfEdges, adjList, deg);


    /*
    // Output of pruferCodeV3gentest
    std::vector<int> ans(numOfEdges);
    for (int i = 0; i < numOfEdges; ++i)
    {
        std::cin >> ans[i];
    }
    
    // Compare pruferCode of Output pruferCodeV3gentest with pruferCode of my program
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
        std::cout << "FAILED";
    */
   
   // Print prufer code
   for (int i = 0; i < numOfEdges - 1; ++i)
   {
       std::cout << pruferCode[i] << ' ';
   }

    return 0;
}