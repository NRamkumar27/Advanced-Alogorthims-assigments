#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_map>

struct Edge {
    int destination;
    int weight;
};

struct Node {
    std::vector<Edge> neighbors;
};

class Graph {
private:
    std::unordered_map<int, Node> nodes;

public:
    void addEdge(int source, int destination, int weight) {
        nodes[source].neighbors.push_back({destination, weight});
    }

    std::pair<std::vector<int>, std::vector<int>> dijkstra(int source) {
        std::vector<int> distances(nodes.size(), std::numeric_limits<int>::max());
        std::vector<int> parent(nodes.size(), -1);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

        distances[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const Edge& neighbor : nodes[u].neighbors) {
                int v = neighbor.destination;
                int weight = neighbor.weight;

                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    parent[v] = u;
                    pq.push({distances[v], v});
                }
            }
        }

        return {distances, parent};
    }

    void printPath(const std::vector<int>& parent, int destination) {
        if (parent[destination] == -1) {
            std::cout << "No path from source to destination." << std::endl;
            return;
        }

        std::vector<int> path;
        for (int v = destination; v != -1; v = parent[v]) {
            path.push_back(v);
        }

        std::cout << "Shortest Path: ";
        for (int i = path.size() - 1; i >= 0; --i) {
            std::cout << path[i];
            if (i > 0) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }

    void userInput() {
        int edges;
        std::cout << "Enter the number of edges: ";
        std::cin >> edges;

        std::cout << "Enter edges (source destination weight):" << std::endl;
        for (int i = 0; i < edges; ++i) {
            int source, destination, weight;
            std::cin >> source >> destination >> weight;
            addEdge(source, destination, weight);
        }
    }
};

int main() {
    Graph graph;

    // User inputs the graph
    graph.userInput();

    int startNode, endNode;
    std::cout << "Enter the starting node: ";
    std::cin >> startNode;
    std::cout << "Enter the ending node: ";
    std::cin >> endNode;

    auto result = graph.dijkstra(startNode);

    std::cout << "Shortest Path Cost: " << result.first[endNode] << std::endl;
    graph.printPath(result.second, endNode);

    return 0;
}
