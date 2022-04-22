# Enemy Clicker

A Project written in C++ using SDL framework.

## Project OverView

All the files with extension `.hpp` are the header files that has function/class defination. And all the files with extension `.cpp`

1. [`Enemy.hpp`](Enemy.hpp) & [`Enemy.cpp`](Enemy.cpp)

    In this project, enemies mean just a rectangle and this file has all the necessary code to create an enemy for us.

2. [`Texture.hpp`](Texture.hpp) & [`Texture.cpp`](Texture.cpp)

   Texture basically means images. These files contain all the code to load , render and free the texture memory whenever required

3. [`Headers.hpp`](Headers.hpp)

    It is the collection of header files especially C++ standard header files and SDL header files.

4. [`Game.hpp`](Game.hpp) & [`Game.cpp`](Game.cpp)

    It is the intergration code of the Game which contain all the varible, function to run the game.

5. [`main.cpp`](main.cpp)

    It include `Game.cpp` and run the game by calling the function that are avaliable in the `Game.cpp`.

6. [`run.sh`](run.sh)

    It is just a basic script file that is used to run the game by command `bash run.sh`.
