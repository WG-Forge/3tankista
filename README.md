# 3tankista #

![GitHub Workflow Status](https://img.shields.io/github/workflow/status/MedoviyKeksik/3tankista/Clang%20format%20lint?label=clang-format)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/MedoviyKeksik/3tankista/Check%20build%20on%20Windows?label=Windows)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/MedoviyKeksik/3tankista/Check%20build%20on%20macos?label=macos)
![GitHub Workflow Status](https://img.shields.io/github/workflow/status/MedoviyKeksik/3tankista/Check%20build%20on%20linux?label=linux)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/MedoviyKeksik/3tankista)

This project is a bot for turn-based strategy game based on World of Tanks.\
Written specifically for the WG-Forge courses.

## Table of Contents

- [About](#about)
- [Install](#install)
- [Usage](#usage)
- [Third party](#third-party)
- [Team](#team)

## About

The game is a turn-based strategy game based on the original World of Tanks game. The game can be played by 3 people, under the control of which there are 5 different types of equipment with their own characteristics.
The battlefield is a hexagonal grid with some special cells (obstacles).

**There are two ways to win:**
1. Capture the central base (score 5 capture points);
2. Score the maximum number of destruction points by the end of the game.

**Tank types and characteristics:**

| Tank Type | HP  | Speed | Damage | Points for destruction |
|-----------|:---:|:-----:|:------:|:----------------------:|
| Light     |  1  |   3   |   1    |           1            |
| Medium    |  2  |   2   |   1    |           2            |
| Heavy     |  3  |   1   |   1    |           3            |
| SPG       |  1  |   1   |   1    |           1            |
| AT-SPG    |  2  |   1   |   1    |           2            |


### Architecture

The project is based on the Entity Component System design pattern. The ECS library we used is a rewritten library of [@tobias-stein](https://github.com/tobias-stein).
[Here](https://tsprojectsblog.wordpress.com/portfolio/entity-component-system/) you can see his post referred to ECS and his library.
Our implementation you can get [here](https://github.com/MedoviyKeksik/ECS).

So everything is divided in three groups:
- Entities
- Components
- Systems

**Entity** represent the main objects of the game (tank, obstacle, etc.) most of which are displayed on the map.\
**Components** store data that is inherent in an **Entity**.\
**Systems** provides functionality with a logic block for working with **Entity** and their **Components**.\
**Systems** communicate with each other using **Events**, which are implemented using the **Observer** pattern.

Internally, the **ECS engine** itself is responsible for allocating memory for the entire objects.

### Graphics

The following technology stack was used to display the data: [OpenGL](https://www.khronos.org/) + [GLFW3](https://www.glfw.org/) + [Glad](https://glad.dav1d.de/), a set of [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) and [FreeType](https://freetype.org/) libraries was used to display textures and text.
All sprites are rendered using the **RenderSystem**, and text is rendered using the **TextRenderer**, which is part of the **RenderSystem**. Shaders are also written (vertex and fragment shaders for displaying sprites and also vertex and fragment shaders for displaying text) using the GLSL language on OpenGL 3.3 Core.

### AI algorithm 

The algorithm of artificial intelligence at this stage of development is very simple. All tanks, regardless of their type, are going to capture the base. At the same time, if an enemy tank gets into their zone of destruction, then the movement stops and they will start shooting at the enemy.

## Install

### Download

Clone this repository and update submodules.
```shell
git clone https://github.com/MedoviyKeksik/3tankista.git
cd 3tankista
git submodule update --init --recursive
```

### Build

Run CMake configure:
```shell
cmake -B build
```

Build with CMake:
```shell
cmake --build build
```

## Usage

Just run ```client``` application in the ```build\src``` folder.

> All text information is entered into the console!\
Until all the information is entered, nothing will be displayed in the window.\
In the future, it is planned to add all input to the GUI. 

**Next you should enter:**
1. Nickname;
2. Password;
3. Game name;
4. Number of turns;
5. Number of players;
6. Is this client is observer (y/n).

![LoginScreenshot](https://user-images.githubusercontent.com/39442984/155405501-141fd2c8-aa9b-46ae-8136-8ed232075196.png)

Now you can enjoy how the bot is playing in real time.

![unknown](https://user-images.githubusercontent.com/39442984/155417865-e2601d82-cbdb-4ad2-bb18-0292d3b124d1.png)

## Third party

- [ASIO](https://think-async.com/Asio/)
- [ECS](https://github.com/MedoviyKeksik/ECS)
- [FreeType](https://freetype.org/)
- [Glad](https://glad.dav1d.de/)
- [GLFW3](https://www.glfw.org/)
- [nlohmann/json](https://github.com/nlohmann/json)
- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)

## Team

- [<img src="https://github.com/Sjarozha.png" title="Sjarozha" width="50" align="center"/>](https://github.com/Sjarozha) - Sergey Titov
- [<img src="https://github.com/MaXMoPKa.png" title="MaXMoPKa" width="50" align="center"/>](https://github.com/MaXMoPKa) - Vladislav Aleynikov
- [<img src="https://github.com/MedoviyKeksik.png" title="MedoviyKeksik" width="50" align="center"/>](https://github.com/MedoviyKeksik) - Klim Severin

Photo of our team when we discuss who committed this bug :)

![7373342587a464f37f1fe93490914339](https://user-images.githubusercontent.com/39442984/155014716-e425f434-ea06-40fc-9fa0-117fa5eeb2c5.png)
