# 3tankista #

![GitHub Workflow Status](https://img.shields.io/github/workflow/status/MedoviyKeksik/3tankista/test-clang-format?label=clang-format)

This project is a bot for turn-based strategy game based on World of Tanks.\
Written specifically for the WG-Forge courses.

## Table of Contents

- [About](#about)
- [Install](#install)
- [Usage](#usage)
- [Third party](#third-party)
- [Team](#team)

## About

The game is a turn-based strategy game based on the original World of tanks game. The game can be played by 3 people, under the control of which there are 5 different types of equipment with their own characteristics.
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

#### Some main systems:

The **ServerSystem** is responsible for establishing a connection and communicating with the game server. [ASIO](https://think-async.com/Asio/) library is used for these purposes. System accepts only 1 event with information about the type of action and data.

The **AdapterSystem** accepts raw data from the **ServerSystem** and parses the JSON in the application models. Then it sends events that are used by all other systems. For parsing JSON AdapterSystem uses [nlohmann/json](https://github.com/nlohmann/json) library.

GameStateSystem

MapSystem

The **GamePlaySystem** is responsible for all actions that need to be done to complete the turn, and for all decisions made by the artificial intelligence of tanks.

>This project is a turn-based game.\
It is necessary with the help of your tanks to get victory in one of two ways: by destruction points, by capture points.\
The game is a client-server application. The exchange with the server is carried out using asio.\
All data( sent and received) is processed using nlohmann/json.\
The application is written using the Entity-Component-System design pattern.

### Graphics


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

**Next you should enter:**
1. Nickname;
2. Password;
3. Game name;
4. Number of turns;
5. Number of players;
6. Is this client is observer (y/n).

![LoginScreenshot](https://user-images.githubusercontent.com/39442984/155405501-141fd2c8-aa9b-46ae-8136-8ed232075196.png)

Now you can enjoy how the bot is playing in real time.

![GUI](https://user-images.githubusercontent.com/39442984/155409635-25975026-7c08-4b2c-a22f-1245f43a48da.png)

## Third party

- [asio](https://think-async.com/Asio/)
- [ecs](https://github.com/MedoviyKeksik/ECS)
- [freetype](https://freetype.org/)
- [glad](https://github.com/Dav1dde/glad)
- [glfw](https://www.glfw.org/)
- [nlohmann/json](https://github.com/nlohmann/json)
- [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)

## Team

- [<img src="https://github.com/Sjarozha.png" title="Sjarozha" width="50" align="center"/>](https://github.com/Sjarozha) - Sergey Titov
- [<img src="https://github.com/MaXMoPKa.png" title="MaXMoPKa" width="50" align="center"/>](https://github.com/MaXMoPKa) - Vladislav Aleynikov
- [<img src="https://github.com/MedoviyKeksik.png" title="MedoviyKeksik" width="50" align="center"/>](https://github.com/MedoviyKeksik) - Severin Klim

Photo of our team when we discuss who committed this bug :)

![7373342587a464f37f1fe93490914339](https://user-images.githubusercontent.com/39442984/155014716-e425f434-ea06-40fc-9fa0-117fa5eeb2c5.png)
