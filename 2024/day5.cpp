#include <bits/stdc++.h>
#include <fstream>

void updateEdges(const std::string ord, std::unordered_map<int, std::vector<int>> &edges) {
    int delimiterIndex = ord.find("|");
    int x = stoi(ord.substr(0, delimiterIndex));
    int y = stoi(ord.substr(delimiterIndex+1, ord.length()-delimiterIndex));
    edges[x].push_back(y);
}

std::vector<int> getPrintOrder(const std::string ord) {
    std::vector<int> printOrder;
    int start = 0, end = 0;
    while((end = ord.find(",", start)) != std::string::npos) {
        printOrder.push_back(stoi(ord.substr(start, end)));
        start = end+1;
    }
    printOrder.push_back(stoi(ord.substr(start)));
    return printOrder;
}

bool dfs(int node, int &cycle_start, std::unordered_map<int, bool> &vis, std::unordered_map<int, int> &parent, std::unordered_map<int, std::vector<int> > graph) {
    vis[node] = 1;
    for (int child: graph[node]) {
        if (vis[child] == 0) {
            parent[child] = node;
            if (dfs(child, cycle_start, vis, parent, graph)) return true;
        } else if (vis[child] == 1) {cycle_start = child; return true;}
    }
    vis[node] = 2;
    return false;
}

// TODO: fix this function
bool canTopSort(const std::unordered_map<int, std::vector<int> > edges) {
    std::cout<< "canTopSort() called"<< std::endl;
    int cycle_start = -1;
    std::unordered_map<int, bool> vis;
    std::unordered_map<int, int> parent;
    for (pair<int, std::vector<int> > nodeChildren: edges)
        if (vis[nodeChildren.first] == 0 && dfs(nodeChildren.first, cycle_start, vis, parent, edges))
            break;
    std::cout<< "cycle start: "<< cycle_start<< std::endl;
    return cycle_start == -1;
}

std::vector<bool> getIsCommonEdge(std::vector<int> printOrder, std::unordered_map<int, std::vector<int> > edges) {
    std::vector<bool> edgeAlreadyPresent(printOrder.size()-1);
    for(int i=1; i<printOrder.size(); ++i) {
        int node1 = printOrder[i-1], node2 = printOrder[i];
        bool edgePresent = false;
        for(int node: edges[node1])
            if(node == node2) {edgePresent = true; break;}
        edgeAlreadyPresent[i-1] = edgePresent;
    }
    return edgeAlreadyPresent;
}

int main() {
    std::unordered_map<int, std::vector<int> > edges;
    std::vector<vector<int> > printOrders;

    ifstream inputFile("./input/day5ex.txt");
    std::string lines;
    bool orderingInput = true;
    while(inputFile >> lines) {
        if(lines=="?") orderingInput = false;
        else if(orderingInput) updateEdges(lines, edges);
        else printOrders.push_back(getPrintOrder(lines));
    }
    inputFile.close();
    long long middlePageOrderSum = 0ll;
    for(std::vector<int> printOrder: printOrders) {
        std::vector<bool> isCommonEdge = getIsCommonEdge(printOrder, edges);
        std::unordered_map<int, std::vector<int> > newEdges = edges;
        for(int i=1; i<printOrder.size(); ++i)
            if(isCommonEdge[i-1] == false) newEdges[printOrder[i-1]].push_back(printOrder[i]);
        if(canTopSort(newEdges)) middlePageOrderSum += printOrder[printOrder.size()/2];   
    }
    std::cout<< "part1: "<< middlePageOrderSum<< std::endl;
    // std::cout<< "part2: "<< x_masCounts<< std::endl;
}