#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure pour représenter une arête du graphe
struct Edge
{
    int destination;
    int weight;
};

// Fonction pour exécuter l'algorithme de Dijkstra
vector<int> Djikstra(const vector<vector<Edge>> &graphe, int start, int n, vector<int> &previous)
{
    vector<int> dist(n, INT_MAX);
    previous.assign(n, -1);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        auto [distanceCourante, noeudCourant] = pq.top();
        pq.pop();

        if (distanceCourante > dist[noeudCourant])
        {
            continue;
        }

        for (const Edge &edge : graphe[noeudCourant])
        {
            int noeudSuivant = edge.destination;
            int newDist = distanceCourante + edge.weight;
            if (newDist < dist[noeudSuivant])
            {
                dist[noeudSuivant] = newDist;
                previous[noeudSuivant] = noeudCourant;
                pq.push({newDist, noeudSuivant});
            }
        }
    }
    return dist;
}

// Fonction pour afficher le chemin vers un nœud
void show_trace_to_node(int node, const vector<int> &prev)
{
    vector<int> trace;
    int current = node;

    // Vérifier si le nœud est atteignable
    if (prev[node] == -1 && node != 0) // Si le nœud est inatteignable et que ce n'est pas le point de départ
    {
        cout << "Aucun chemin vers le nœud " << node << endl;
        return;
    }

    while (current != -1)
    {
        trace.push_back(current);
        current = prev[current];
    }

    for (int i = trace.size() - 1; i >= 0; --i)
    {
        cout << trace[i];
        if (i > 0)
        {
            cout << "->";
        }
    }
    cout << endl;
}

int main()
{
    int n = 6;
    vector<vector<Edge>> graph(n);
    graph[0] = {{1, 4}, {2, 1}};         // Nœud 0 a des arêtes vers 1 (poids 4) et 2 (poids 1)
    graph[1] = {{0, 4}, {3, 1}, {2, 2}}; // Nœud 1 a des arêtes vers 0 (poids 4) et 3 (poids 1)
    graph[2] = {{0, 1}, {3, 5}, {1, 1}}; // Nœud 2 a des arêtes vers 0 (poids 1) et 3 (poids 5)
    graph[3] = {{1, 1}, {2, 5}, {4, 3}}; // Nœud 3 a des arêtes vers 1 (poids 1), 2 (poids 5) et 4 (poids 3)
    graph[4] = {{3, 3}, {5, 1}};         // Nœud 4 a des arêtes vers 3 (poids 3) et 5 (poids 1)
    graph[5] = {{4, 1}};

    int start = 3;
    vector<int> previous;
    vector<int> distances = Djikstra(graph, start, n, previous);

    cout << "Distances à partir du nœud " << start << " :\n";
    for (int i = 0; i < n; ++i)
    {
        if (distances[i] == INT_MAX)
            cout << "Nœud " << i << ": INF" << endl;
        else
            cout << "Nœud " << i << ": " << distances[i] << endl;
    }

    show_trace_to_node(2, previous); // Afficher le chemin jusqu'au nœud 5

    return 0;
}
