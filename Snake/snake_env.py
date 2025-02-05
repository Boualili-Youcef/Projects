import numpy as np
import random

# Constantes de l'environnement
GRID_SIZE = (20, 20)
FOOD_REWARD = 10
COLLISION_PENALTY = -10
STEP_PENALTY = -0.1

class SnakeEnv:
    def __init__(self):
        # ...existing code...
        self.grid_width, self.grid_height = GRID_SIZE
        self.reset()

    def reset(self):
        # Initialise la position de la snake au centre et place la nourriture.
        self.snake = [(self.grid_width//2, self.grid_height//2)]
        self.direction = (0, -1)  # déplacement vers le haut par défaut
        self._place_food()
        self.score = 0
        return self._get_state()

    def _place_food(self):
        # Place la nourriture aléatoirement en évitant la snake.
        empty = [(x, y) for x in range(self.grid_width) for y in range(self.grid_height) if (x, y) not in self.snake]
        self.food = random.choice(empty)

    def _get_state(self):
        # Retourne un état simple sous forme d'une matrice (peut être adapté)
        state = np.zeros(GRID_SIZE)
        for x, y in self.snake:
            state[y][x] = 1
        fx, fy = self.food
        state[fy][fx] = 2
        return state

    def step(self, action):
        # Action est dans {0: haut, 1: droite, 2: bas, 3: gauche}
        dx, dy = [(0, -1), (1, 0), (0, 1), (-1, 0)][action]
        # Mise à jour de la direction si action opposée non autorisée peut être ajoutée
        self.direction = (dx, dy)
        head = self.snake[0]
        new_head = (head[0] + dx, head[1] + dy)
        
        reward = STEP_PENALTY
        done = False

        # Vérification collision murale
        if new_head[0] < 0 or new_head[0] >= self.grid_width or new_head[1] < 0 or new_head[1] >= self.grid_height:
            reward = COLLISION_PENALTY
            done = True
        # Vérification collision avec soi-même
        elif new_head in self.snake:
            reward = COLLISION_PENALTY
            done = True
        else:
            self.snake.insert(0, new_head)
            # Si nourriture consommée, renvoie du reward, sinon retire la queue
            if new_head == self.food:
                reward = FOOD_REWARD
                self.score += 1
                self._place_food()
            else:
                self.snake.pop()

        new_state = self._get_state()
        return new_state, reward, done, {}

    def render(self):
        # Méthode de rendu textuel (pour l'exemple)
        state = self._get_state()
        for row in state:
            print(' '.join(str(int(x)) for x in row))
        print("Score:", self.score)
