#include <bits/stdc++.h>
using namespace std;

// Function to perform DFS and fill the stack according to the finishing times
void dfs1(int node, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& finishStack) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs1(neighbor, adj, visited, finishStack);
        }
    }
    finishStack.push(node);  // Store node after visiting all its neighbors
}

// Function to perform DFS on the reversed graph
void dfs2(int node, vector<vector<int>>& adjRev, vector<bool>& visited, vector<int>& component) {
    visited[node] = true;
    component.push_back(node);
    for (int neighbor : adjRev[node]) {
        if (!visited[neighbor]) {
            dfs2(neighbor, adjRev, visited, component);
        }
    }
}

// Main function to find and print all SCCs
void findSCCs(int n, vector<vector<int>>& adj) {
    stack<int> finishStack;
    vector<bool> visited(n + 1, false);

    // Step 1: Perform DFS and push nodes into the stack based on finishing time
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs1(i, adj, visited, finishStack);
        }
    }

    // Step 2: Reverse the graph
    vector<vector<int>> adjRev(n + 1);
    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            adjRev[v].push_back(u);  // Reverse the edge
        }
    }

    // Step 3: Perform DFS on the reversed graph in the order of finishStack
    fill(visited.begin(), visited.end(), false);  // Reset the visited array
    while (!finishStack.empty()) {
        int node = finishStack.top();
        finishStack.pop();

        if (!visited[node]) {
            vector<int> component;
            dfs2(node, adjRev, visited, component);  // Find one SCC

            // Print the current SCC
            for (int u : component) {
                cout << u << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;  // Number of nodes and edges
    vector<vector<int>> adj(n + 1);

    // Input edges
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);  // Directed edge from u to v
    }

    // Find and print all strongly connected components
    findSCCs(n, adj);

    return 0;
}
