# Projet ECommerce

Ce projet est une application e-commerce full-stack composée d'un backend Node.js/Express et d'un frontend React.

## Prérequis

- Node.js (version 12 ou plus)
- MongoDB (instance locale ou hébergée)
- npm ou yarn

## Installation

### Backend

1. Se placer dans le répertoire du backend :
   ```bash
   cd backend
   ```
2. Installer les dépendances :
   ```bash
   npm install
   ```
3. Configurer les variables d'environnement (par exemple, créer un fichier `.env`) :
   ```
   PORT=5000
   MONGODB_URI=your_mongodb_connection_string
   ```
4. Lancer le serveur :
   ```bash
   npm start
   ```

### Frontend

1. Se placer dans le répertoire du frontend :
   ```bash
   cd frontend/mini-ecommerce
   ```
2. Installer les dépendances :
   ```bash
   npm install
   ```
3. Lancer l'application frontend :
   ```bash
   npm start
   ```

## Utilisation

- Le serveur backend sera disponible sur `http://localhost:5000`
- Le frontend est accessible sur `http://localhost:3000`

## Structure du projet

- `/backend` : contient le code du serveur (routes, modèles, etc.)
- `/frontend` : contient le code de l'application React

## Remarques

- Assurez-vous que MongoDB est lancé ou accessible via la chaîne de connexion.
- Pour toute aide supplémentaire, consultez la documentation des technologies utilisées.

## Lancer MongoDB

Si vous souhaitez lancer MongoDB en local, suivez ces étapes :

1. Assurez-vous que MongoDB est installé sur votre machine.
2. Lancez le serveur MongoDB avec la commande :
   ```bash
   mongod
   ```
   Cette commande démarre le service sur le port par défaut (27017).
3. Vérifiez que le service fonctionne en vous connectant via le client mongo :
   ```bash
   mongo
   ```
