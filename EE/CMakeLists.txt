# Spécifier la version minimale de CMake
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(JustCollecte)

# Spécifier la version du C++ utilisée
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajouter les répertoires contenant les fichiers d'en-tête (.hpp)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Ajouter les répertoires contenant les fichiers sources (.cpp)
# (tu peux aussi organiser tes sources en sous-dossiers si nécessaire)
set(SOURCE_FILES 
    src/ressources/Ressource.cpp
    src/ressources/Trees/Tree.cpp
    src/npc/Citizen.cpp
    src/ressources/Trees/Olk.cpp
    src/ressources/ores/Ores.cpp
    src/ressources/Trees/Pine.cpp
    src/npc/Unit.cpp
    src/buildings/Building.cpp
    src/buildings/Depot.cpp
    src/buildings/Home.cpp
    src/game/Game.cpp

)

# Ajouter l'exécutable du projet (fichier source principal)
add_executable(JustCollecte main.cpp ${SOURCE_FILES})

# Trouver et lier les bibliothèques SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(JustCollecte sfml-graphics sfml-window sfml-system)