import math

class Graphe:
    def __init__(self, nodes):
        self.nodes = set(nodes)  # Le set pour s'assurer qu'il n'y a pas de doublons
        self.aretes = {}  # dictionnaire pour stocker les arêtes
        self.distance = {}
        self.f = {}
        self.prec = {}
    
    def ajout_noeud(self, u, v, poid):
        if u in self.nodes and v in self.nodes:
            self.aretes[(u, v)] = poid
            self.aretes[(v, u)] = poid  
    
    def afficher(self):
        print("Sommets :", self.nodes)
        print("Arêtes :")
        for (u, v), poids in self.aretes.items():
            print(f"{u} --({poids})--> {v}")

    def dijkstra(self, depart, arriver):
        E = [depart]
        for a in self.nodes:
            self.distance[a] = math.inf
            self.prec[a] = None 
        self.distance[depart] = 0
        while E:
            u = E.pop(0)
            if u == arriver:
                return (self.distance[u], self.prec[u])
            for (x, y), poid in self.aretes.items():
                if x == u:
                    alt = self.distance[u] + poid
                    if alt < self.distance[y]:
                        self.distance[y] = alt
                        self.prec[y] = x
                        if y not in E:
                            E.append(y)
                            
    """                    
    def heuristique(self, depart, arriver):
        return math.sqrt((arriver.x -depart.x)**2 + (arriver.y -depart.y)**2)
    
    
    def dijkstra(self, depart, arriver):
        E = [depart]
        for a in self.nodes:
            self.distance[a] = math.inf
            self.f[a] = math.inf
            self.prec[a] = None 
        self.distance[depart] = 0
        self.f[depart] = self.heuristique() #coordionnees
        while E:
            u = min() #minimise f 
            u = E.remove(0)
            if u == arriver:
                return (self.distance[u], self.prec[u])
            for (x, y), poid in self.aretes.items():
                if x == u:
                    alt = self.distance[u] + poid
                    if alt < self.distance[y]:
                        self.distance[y] = alt
                        self.prec[y] = x
                        self.f[y] = self.distance[y] + self.heuristique(v)
                        if y not in E:
                            E.append(y)
    """
    def trace_route(self, arriver):
        listes = [arriver]
        while self.prec[arriver] is not None:
            pre = self.prec[arriver]
            listes.append(pre)
            arriver = pre
        listes.reverse()
        return listes


graphe = Graphe({0, 1, 2, 3, 4, 5})

# Ajout d'arêtes
graphe.ajout_noeud(0, 1, 1)
graphe.ajout_noeud(0, 2, 3)
graphe.ajout_noeud(1, 3, 2)
graphe.ajout_noeud(2, 4, 4)
graphe.ajout_noeud(3, 4, 2)
graphe.ajout_noeud(3, 5, 6)
graphe.ajout_noeud(4, 5, 2)

# Affichage du graphe
graphe.afficher()    

# Calcul de la distance et des prédécesseurs avec Dijkstra
d, p = graphe.dijkstra(0, 5)
print("Distance :", d)
print("Prédécesseurs :", p)

# Traçage du chemin
chemin = graphe.trace_route(5)
print("Chemin :", chemin)
