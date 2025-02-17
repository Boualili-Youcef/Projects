import sys, random, pygame
from agent import RLAgent
from config import WIDTH, HEIGHT, BLOCK_SIZE  # import des constantes depuis config.py
import matplotlib.pyplot as plt
import threading

# Couleurs
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
BLUE = (0, 0, 255)

global_counter = 0  # compteur global

class Snake:
    def __init__(self, color, init_pos):
        self.color = color
        self.body = [init_pos]
        self.direction = (0, -BLOCK_SIZE)

    def move(self, grow=False):  # ajout du paramètre grow
        head = self.body[0]
        new_head = (head[0] + self.direction[0], head[1] + self.direction[1])
        self.body.insert(0, new_head)
        if not grow:
            self.body.pop()

    def grow(self):
        tail = self.body[-1]
        self.body.append(tail)

    def change_direction(self, new_direction):
        # Empêche le mouvement inverse
        if (new_direction[0] + self.direction[0], new_direction[1] + self.direction[1]) != (0, 0):
            self.direction = new_direction

    def draw(self, win):
        for part in self.body:
            pygame.draw.rect(win, self.color, (part[0], part[1], BLOCK_SIZE, BLOCK_SIZE))

    def collides(self, pos):
        return pos in self.body

def place_food(snake):
    cols = WIDTH // BLOCK_SIZE
    rows = HEIGHT // BLOCK_SIZE
    while True:
        pos = (random.randint(0, cols - 1) * BLOCK_SIZE, random.randint(0, rows - 1) * BLOCK_SIZE)
        if not snake.collides(pos):
            return pos

def main():
    pygame.init()
    # Pour "training" on peut choisir une fenêtre réduite ou même aucune affichage
    win = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("Snake RL")
    clock = pygame.time.Clock()
    font = pygame.font.SysFont("Arial", 20)
    
    # Lire le mode depuis sys.argv (default = "human")
    mode = sys.argv[1] if len(sys.argv) > 1 else "human"
    # Modes possibles: "human", "ai", "human_vs_ai", "ai_vs_ai", "training"
    
    plt.ion()
    fig, ax = plt.subplots()
    rounds = []
    scores = []
    round_number = 1
    perf_threshold = 5           # ajout du seuil de performance
    achieved_threshold = False   # indicateur de seuil atteint

    # Créer agent(s) selon le mode
    if mode in ["ai", "training"]:
        agent1 = RLAgent()
    elif mode == "human_vs_ai":
        agent1 = RLAgent()  # pour le serpent IA
    elif mode == "ai_vs_ai":
        agent1 = RLAgent()
        agent2 = RLAgent()
    
    # Remplacer le compteur global par des compteurs locaux
    if mode in ["human_vs_ai", "ai_vs_ai"]:
        # Ils seront initialisés à chaque round
        pass
    else:
        counter = 0

    game_running = True   # Correction de l'erreur

    while game_running:
        # Initialisation des compteurs de pas selon le mode
        if mode in ["human_vs_ai", "ai_vs_ai"]:
            step_counter1 = 0
            step_counter2 = 0
        else:
            counter = 0
        # Pour modes multi-serpent, on initialise chaque serpent à la même position de départ
        init = ((WIDTH // 2 // BLOCK_SIZE) * BLOCK_SIZE, (HEIGHT // 2 // BLOCK_SIZE) * BLOCK_SIZE)
        if mode in ["human_vs_ai", "ai_vs_ai"]:
            snake1 = Snake(GREEN, init)  # serpent 1
            snake2 = Snake(BLUE, init)   # serpent 2
            food = place_food(snake1)    # On utilise le même aliment pour les deux
        else:
            snake1 = Snake(GREEN, init)
            food = place_food(snake1)
        # Pour "training", on n'a qu'un serpent IA

        # Initialize scores: two scores for multiplayer or one for single player
        if mode in ["human_vs_ai", "ai_vs_ai"]:
            score1 = 0
            score2 = 0
        else:
            score1 = 0
        round_running = True

        # Etat initial pour chaque serpent (pour IA on utilise snake1, et pour le second serpent si besoin)
        state1 = {
            'head': snake1.body[0],
            'food': food,
            'direction': snake1.direction,
            'body': snake1.body[1:]
        }
        if mode == "human_vs_ai":
            state2 = {
                'head': snake2.body[0],
                'food': food,
                'direction': snake2.direction,
                'body': snake2.body[1:]
            }
        if mode == "ai_vs_ai":
            state2 = {
                'head': snake2.body[0],
                'food': food,
                'direction': snake2.direction,
                'body': snake2.body[1:]
            }

        while round_running:
            clock.tick(5 if mode != "training" else 40)
            # Incrémentation des compteurs spécifiques selon le mode
            if mode in ["human_vs_ai", "ai_vs_ai"]:
                step_counter1 += 1
                step_counter2 += 1
            else:
                counter += 1
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    game_running = False
                    round_running = False
                # Pour modes impliquant un humain
                if mode in ["human", "human_vs_ai"] and event.type == pygame.KEYDOWN:
                    # Contrôle pour le serpent humain (toujours snake1)
                    if event.key == pygame.K_UP:
                        snake1.change_direction((0, -BLOCK_SIZE))
                    elif event.key == pygame.K_DOWN:
                        snake1.change_direction((0, BLOCK_SIZE))
                    elif event.key == pygame.K_LEFT:
                        snake1.change_direction((-BLOCK_SIZE, 0))
                    elif event.key == pygame.K_RIGHT:
                        snake1.change_direction((BLOCK_SIZE, 0))
            
            # Mise à jour des actions selon le mode
            if mode in ["ai", "training"]:
                # Seulement snake1 piloté par l'IA
                action = agent1.choose_action(state1)
                directions = [(0, -BLOCK_SIZE), (BLOCK_SIZE, 0), (0, BLOCK_SIZE), (-BLOCK_SIZE, 0)]
                snake1.change_direction(directions[action])
            elif mode == "human_vs_ai":
                # snake1 est humain, snake2 est IA
                action = agent1.choose_action(state2)
                directions = [(0, -BLOCK_SIZE), (BLOCK_SIZE, 0), (0, BLOCK_SIZE), (-BLOCK_SIZE, 0)]
                snake2.change_direction(directions[action])
            elif mode == "ai_vs_ai":
                # Les deux serpents sont IA
                action1 = agent1.choose_action(state1)
                action2 = agent2.choose_action(state2)
                directions = [(0, -BLOCK_SIZE), (BLOCK_SIZE, 0), (0, BLOCK_SIZE), (-BLOCK_SIZE, 0)]
                snake1.change_direction(directions[action1])
                snake2.change_direction(directions[action2])
            
            # Pour chaque serpent, on calcule le prochain head et on avance
            # On ne gère qu'un seul aliment commun
            # Serpent 1
            prev_state1 = state1
            next_head1 = (snake1.body[0][0] + snake1.direction[0], snake1.body[0][1] + snake1.direction[1])
            ate1 = (next_head1 == food)
            if ate1:
                reward1 = 10
                score1 += 1   # increment snake1's score
                snake1.move(grow=True)
                food = place_food(snake1)
            else:
                reward1 = -0.1
                snake1.move()
            head1 = snake1.body[0]
            if head1[0] < 0 or head1[0] >= WIDTH or head1[1] < 0 or head1[1] >= HEIGHT or head1 in snake1.body[1:]:
                reward1 = -10
                if mode in ["ai", "training", "human_vs_ai", "ai_vs_ai"]:
                    if mode in ["ai", "training", "human_vs_ai"]:
                        threading.Thread(target=agent1.learn, args=(prev_state1, action if mode!="human" else None, reward1, None, True)).start()
                    elif mode == "ai_vs_ai":
                        threading.Thread(target=agent1.learn, args=(prev_state1, action1, reward1, None, True)).start()
                round_running = False  # fin du round en cas de mort
                # Aucun délai ni attente : le round se relance directement
                continue
            # Actualisation de l'état pour snake1
            # Calcul des distances aux murs
            dist_up = head1[1]
            dist_down = HEIGHT - head1[1]
            dist_left = head1[0]
            dist_right = WIDTH - head1[0]
            if dist_up < BLOCK_SIZE or dist_down < BLOCK_SIZE or dist_left < BLOCK_SIZE or dist_right < BLOCK_SIZE:
                reward1 -= 1
            state1 = {
                'head': head1,
                'food': food,
                'direction': snake1.direction,
                'body': snake1.body[1:],
                'wall_distances': (dist_up, dist_down, dist_left, dist_right)
            }
            # Apprentissage pour snake1 si IA ou entraînement
            if mode in ["ai", "training"]:
                threading.Thread(target=agent1.learn, args=(prev_state1, action, reward1, state1, False)).start()
            elif mode == "ai_vs_ai":
                threading.Thread(target=agent1.learn, args=(prev_state1, action1, reward1, state1, False)).start()
            
            # Pour modes à deux serpents, on traite snake2 également
            if mode in ["human_vs_ai", "ai_vs_ai"]:
                prev_state2 = state2
                next_head2 = (snake2.body[0][0] + snake2.direction[0], snake2.body[0][1] + snake2.direction[1])
                ate2 = (next_head2 == food)
                if ate2:
                    reward2 = 10
                    score2 += 1   # increment snake2's score
                    snake2.move(grow=True)
                    food = place_food(snake2)
                else:
                    reward2 = -0.1
                    snake2.move()
                head2 = snake2.body[0]
                if head2[0] < 0 or head2[0] >= WIDTH or head2[1] < 0 or head2[1] >= HEIGHT or head2 in snake2.body[1:]:
                    reward2 = -10
                    if mode == "human_vs_ai":
                        threading.Thread(target=agent1.learn, args=(prev_state2, action, reward2, None, True)).start()
                    elif mode == "ai_vs_ai":
                        threading.Thread(target=agent2.learn, args=(prev_state2, action2, reward2, None, True)).start()
                    round_running = False
                    continue
                state2 = {
                    'head': head2,
                    'food': food,
                    'direction': snake2.direction,
                    'body': snake2.body[1:]
                }
                if mode == "ai_vs_ai":
                    threading.Thread(target=agent2.learn, args=(prev_state2, action2, reward2, state2, False)).start()
            
            # Affichage pour tous les modes, y compris "training"
            win.fill(BLACK)
            pygame.draw.rect(win, RED, (food[0], food[1], BLOCK_SIZE, BLOCK_SIZE))
            snake1.draw(win)
            if mode in ["human_vs_ai", "ai_vs_ai"]:
                snake2.draw(win)
                score_text = font.render(f"Score1: {score1} | Score2: {score2}", True, WHITE)
            else:
                score_text = font.render(f"Score: {score1}", True, WHITE)
            win.blit(score_text, (10, 10))
            pygame.display.update()
        # Fin du round, affichage du score
        if mode in ["human_vs_ai", "ai_vs_ai"]:
            print(f"Round {round_number} terminé - Score1: {score1} | Score2: {score2}")
        else:
            print(f"Round {round_number} terminé - Score: {score1}")
        rounds.append(round_number)
        scores.append(score1)
        ax.clear()
        #ax.plot(rounds, scores, label="Score")
        #ax.legend()
        #plt.pause(0.001)
        if score1 >=  perf_threshold and achieved_threshold is False:
            achieved_threshold = True
            print("Seuil de performance atteint !")
        round_number += 1

    # Sauvegarde des agents en mode entraînement or IA
    if mode in ["ai", "training", "human_vs_ai", "ai_vs_ai"]:
        if mode in ["human_vs_ai", "ai_vs_ai"]:
            agent1.save(); 
            if mode == "ai_vs_ai":
                agent2.save()
        else:
            agent1.save()
    pygame.quit()

if __name__ == "__main__":
    main()