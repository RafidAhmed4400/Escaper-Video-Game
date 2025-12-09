**Escaper Game**

A top-down dungeon survival game built in C++ using SDL2 and OpenGL/GLSL. This project features multi-scene gameplay, animated player sprites, dungeon-style levels, sound effects, and background music.

<br> 
<br>

**Features:**

- Multi-scene system (Menu, Main, Dungeon, Win, Lose)

- Animated player movement with sprite sheets

- Tile-based dungeon maps

- Camera that follows the player

- Sound effects and looping background music

- Fixed timestep game loop for consistent movement

<br> 
<br>

**Technologies Used:**

- C++

- SDL2

- OpenGL

- GLSL Shaders

- SDL_mixer

- GLM

<br> 
<br>

**Controls:**

**Player:**

- Left Arrow – Move Left

- Right Arrow – Move Right

- Up Arrow – Move Up

- Down Arrow – Move Down

- Enter – Start game (from Menu)

<br>
<br>

**Extra Mechanics:**

- Multiple dungeon levels

- Player lives system

- Scene switching between dungeons and end states

<br>
<br>

**Game Rules:**

- Navigate through dungeons to survive.

- Avoid enemies and dangerous tiles.

- Losing all lives results in a game over.

- Clearing all dungeons results in a win.

<br>
<br>

**Project Structure:**

- /project-root

- main.cpp

- ShaderProgram.h / ShaderProgram.cpp

- Entity.h / Entity.cpp

- Map.h / Map.cpp

- Utility.h / Utility.cpp

- Scenes/Scene.h

- Menu.h / Menu.cpp

- Main.h / Main.cpp

- Dungeon.h / Dungeon.cpp

- Win.h / Win.cpp

- Lose.h / Lose.cpp

- shaders/

- vertex_textured.glsl

- fragment_textured.glsl

- assets/

- player.png

- tiles.png

- audio / Great Little Challenge.mp3 / bounce.wav

<br>
<br>

**How to Run:**

**Prerequisites:**

- Install SDL2, OpenGL, GLM, and SDL_mixer.

**Build (example using g++):**

- g++ main.cpp *.cpp -lSDL2 -lSDL2_mixer -lOpenGL -ldl -o escaper

**Run:**

- ./escaper
