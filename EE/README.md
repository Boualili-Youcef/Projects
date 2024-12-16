# JustCollecte

JustCollecte is a simple simulation where multiple citizens move towards a resource and gather it. The simulation uses SFML for graphical representation and C++ threads for concurrent execution.

## Features

- Multiple citizens move towards a resource.
- Citizens gather resources independently once they reach the resource.
- Smooth movement and resource gathering visualization using SFML.

## Requirements

- C++17 or later
- SFML library

## Installation

### Linux

1. Install SFML:

    ```sh
    sudo apt-get install libsfml-dev
    ```

2. Clone the repository:

    ```sh
    git clone https://github.com/yourusername/JustCollecte.git
    cd JustCollecte
    ```

3. Create a build directory and compile the project using CMake:

    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

4. Run the executable:

    ```sh
    ./JustCollecte
    ```

## Project Structure

The project consists of the following main directories and files:

- `src/`: Contains the source code files.
- `include/`: Contains the header files.
- `CMakeLists.txt`: The CMake configuration file for building the project.

## Usage

- The simulation window will open, showing multiple citizens moving towards a resource.
- Each citizen will start gathering resources independently once they reach the resource.

## Acknowledgements
- [SFML](https://www.sfml-dev.org/) - Simple and Fast Multimedia Library