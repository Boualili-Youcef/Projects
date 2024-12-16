#include <iostream> // Pour les entrées/sorties (cout, cin)
#include <vector>   // Pour utiliser std::vector (graphe en liste d'adjacence)
#include <queue>    // Pour utiliser std::priority_queue (file de priorité)
#include <climits>  // Pour utiliser INT_MAX (représentation d'une distance infinie)

using namespace std;

// Structure pour représenter une arête du graphe
struct Edge
{
    int destination; // Destination de l'arête
    int weight;      // Poids (ou coût) de l'arête
};

// Fonction pour exécuter l'algorithme de Dijkstra
vector<int> dijkstra(int start, int n, const vector<vector<Edge>> &graph)
{
    // Initialiser un tableau pour stocker les distances minimales depuis le nœud de départ
    vector<int> dist(n, INT_MAX); // Pour initialiser toutes les distances à "infini"
    dist[start] = 0;              // La distance depuis le nœud de départ à lui-même est 0

    // Priority queue (file de priorité) pour explorer les nœuds dans l'ordre des distances les plus courtes
    // La file stocke des paires (distance, nœud) c'est indiquer par le premier 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // ici on une priority_queue qui permet de sortir par defaut
                                                                          // le plus grand element mais avec greayter<> on peut sortir le plus petit element
    pq.push({0, start}); // Ajouter le nœud de départ avec une distance initiale de 0

    // Tant qu'il y a des nœuds à traiter
    while (!pq.empty())
    {
        // Extraire le nœud avec la distance minimale (top de la priority queue) et destructuration avec auto [var1, var2]
        auto [currentDistance, currentNode] = pq.top();
        // Puis pop 
        pq.pop();

        // Si la distance actuelle est plus grande que celle enregistrée, on l'ignore (optimisation)
        if (currentDistance > dist[currentNode])
            continue; // Saute une itération de la boucle

        // Parcourir tous les voisins (arêtes sortantes) du nœud actuel
        for (const Edge &edge : graph[currentNode])
        {
            int nextNode = edge.destination;             // Destination de l'arête
            int newDist = currentDistance + edge.weight; // Calculer la distance via ce nœud

            // Si on trouve un chemin plus court vers nextNode, on met à jour
            if (newDist < dist[nextNode])
            {
                dist[nextNode] = newDist;     // Mettre à jour la distance minimale
                pq.push({newDist, nextNode}); // Ajouter le nœud voisin dans la file de priorité
            }
        }
    }

    return dist; // Retourner le tableau des distances minimales
}

int main()
{
    int n = 6;                     // Nombre total de nœuds dans le graphe
    vector<vector<Edge>> graph(n); // Graphe représenté comme une liste d'adjacence

    // Ajouter les arêtes au graphe
    // Exemple : graph[u] contient toutes les arêtes sortant du nœud u
    graph[0] = {{1, 4}, {2, 1}}; // Nœud 0 a des arêtes vers 1 (poids 4) et 2 (poids 1)
    graph[1] = {{3, 1}};         // Nœud 1 a une arête vers 3 (poids 1)
    graph[2] = {{1, 2}, {3, 5}}; // Nœud 2 a des arêtes vers 1 (poids 2) et 3 (poids 5)
    graph[3] = {{4, 3}};         // Nœud 3 a une arête vers 4 (poids 3)
    graph[4] = {{5, 1}};         // Nœud 4 a une arête vers 5 (poids 1)
    graph[5] = {};               // Nœud 5 n'a pas d'arêtes sortantes

    int start = 0;                                     // Définir le nœud de départ pour Dijkstra
    vector<int> distances = dijkstra(start, n, graph); // Exécuter Dijkstra

    // Afficher les distances minimales depuis le nœud de départ
    cout << "Distances à partir du nœud " << start << " :\n";
    for (int i = 0; i < n; ++i)
    {
        if (distances[i] == INT_MAX) // Si la distance est toujours "infinie", le nœud est inatteignable
            cout << "Nœud " << i << ": INF" << endl;
        else
            cout << "Nœud " << i << ": " << distances[i] << endl;
    }

    return 0;
}
