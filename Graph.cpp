#include "Graph.h"

Graph::Graph(int num, bool dir): n(num), hasDir(dir), nodes(num +1) {}

void Graph::addEdge(int src, int dest, int weight) {
    if (src < 1 || src > n || dest < 1 || dest > n) {return;}
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) {nodes[dest].adj.push_back({src, weight});}
}

vector<string> Graph::dfs(int v,string partida,string destino) {
    cout << v << " "; // show node order
    nodes[v].visited = true ;
    scales.push_back(nodes[v].flight->getSource()->getCode());
    for (auto e : nodes[v]. adj) {
        string test = nodes[v].flight->getSource()->getCode();
        if(nodes[v].flight->getSource()->getCode() == destino){
            return scales;
        }
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w,partida,destino);
    }
}
/*
void Graph::DFS(int s)
{
    // Initially mark all vertices as not visited
    vector<bool> visited(V, false);

    // Create a stack for DFS
    stack<int> stack;

    // Push the current source node.
    stack.push(s);

    while (!stack.empty())
    {
        // Pop a vertex from stack and print it
        int s = stack.top();
        stack.pop();

        // Stack may contain same vertex twice. So
        // we need to print the popped item only
        // if it is not visited.
        if (!visited[s])
        {
            cout << s << " ";
            visited[s] = true;
        }

        // Get all adjacent vertices of the popped vertex s
        // If a adjacent has not been visited, then push it
        // to the stack.
        for (auto i = adj[s].begin(); i != adj[s].end(); ++i)
            if (!visited[*i])
                stack.push(*i);
    }
}*/

list<Flight*> Graph::bfsGetList(int v) {
    // initialize all nodes as unvisited
    for (int v = 1; v <= n; v++) {nodes[v].visited = false;}
    list<Flight*> list1;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    int i = 1;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front();
        q.pop (); // remove first element of q
        list1.push_back(nodes[u].flight);
        if (i == 1) {
            pair<string, int> p;
            p.first = nodes[u].flight->getSource()->getCode();
            p.second = u;
        }
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) { // new node!
                q.push(w);
                nodes[w].visited = true;
            }
        }
        i++;
    }
    return list1;
}

void Graph::setFlight(int node, Flight* f) {
    nodes[node].flight = f;
}

