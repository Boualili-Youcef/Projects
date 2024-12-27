cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(ChessGame)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ajouter les fichiers sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Inclure les répertoires d'en-têtes
include_directories(include)

# Trouver les packages SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Créer l'exécutable
add_executable(ChessGame ${SOURCES})

# Lier les bibliothèques SFML
target_link_libraries(ChessGame sfml-graphics sfml-window sfml-system)

# Copier les ressources dans le répertoire de build
add_custom_command(TARGET ChessGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/Textures $<TARGET_FILE_DIR:ChessGame>/Textures)