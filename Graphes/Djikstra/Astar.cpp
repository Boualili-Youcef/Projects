#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using std::cout, std::endl, std::cin;

struct Edge {
    int destination;
    int weight;
};

std::vector<int> Astar(std::vector<std::vector<Edge>>& graph, int size, int start, int end){
    std::vector<int> dist(size, INT_MAX);
    dist[start] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        auto [distanceCourante, noeudCourant] = pq.top();
        pq.pop();

        if (distanceCourante > dist[noeudCourant])
        {
            continue;
        }

        for (const Edge &edge : graph[noeudCourant])
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

int main(){
    return 0;
}