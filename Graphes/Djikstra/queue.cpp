#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::priority_queue<int,std::vector<int>, std::greater<>> pq; // Max-heap par défaut

    pq.push(10);
    pq.push(20);
    pq.push(5);

    // Accès à l'élément le plus prioritaire (le plus grand)
    std::cout << "Top: " << pq.top() << "\n"; // 20

    pq.pop(); // Supprime l'élément le plus prioritaire (20)
    std::cout << "Top après pop: " << pq.top() << "\n"; // 10

    return 0;
}
