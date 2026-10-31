# Terminal Hacker

Terminal Hacker is a C++ console game. The player explores a virtual network, solves code puzzles, and passes firewalls.

This project is a learning simulation. It does not connect to real servers or networks.

## Features

- A 5 x 5 network map with keyboard movement
- Five servers with XP access rules
- Four-digit code puzzles with five tries per run
- Three firewall levels: odd/even, array sum, and table search
- Player energy, XP, level, and detection risk
- A game report with task progress and success rate
- Win and loss rules
- Input checks and map boundary checks

## Requirements

- A C++ compiler with C++11 support or newer
- A terminal

No extra libraries are needed.

## Build and Run

Open a terminal in the project folder.

Build:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp Player.cpp Server.cpp Task.cpp Game.cpp Input.cpp -o hacker
```

Run on macOS or Linux:

```bash
./hacker
```

On Windows, use `-o hacker.exe` when building, then run `.\hacker.exe` in PowerShell.

## How to Play

1. Choose `1` to open the network map.
2. Move with `W`, `S`, `A`, and `D`. Press Enter after each move.
3. Find a server cell, then press `Q` to return to the menu.
4. Choose `2` to connect to the server.
5. Choose `3` to solve its code and earn XP.
6. Choose `4` to pass its firewall.
7. Complete both tasks on all five servers to win.

Choose `5` to view player status, `6` to view the report, or `0` to exit.

### Map Symbols

| Symbol | Meaning |
| --- | --- |
| 0 | Empty cell |
| 1 | Server |
| 2 | Security point |
| 3 | Player |

Security points are map markers. They do not cause damage. Opening the map ends the current connection, so connect again before starting a task.

## Game Rules

The player starts with 100 energy, 0 XP, level 1, and 0% risk.

- A wrong code guess costs 10 energy and adds 5% risk.
- A code run allows five valid guesses. A new run is allowed if the player is still active.
- A wrong firewall answer costs 10 energy and adds 10% risk.
- Invalid text input does not use a code guess or cost energy.
- Each server gives its XP reward only once, when its code is solved.
- The firewall becomes available after that server's code is solved.
- Each 100 XP adds one player level.
- The game ends when energy reaches 0 or risk reaches 100%.
- Completing all ten tasks wins the game.
- Progress resets when the program closes.

### Servers

| Server | Difficulty | XP Needed | XP Reward |
| --- | --- | --- | --- |
| Training Server | Easy | 0 | 100 |
| Data Server | Easy | 100 | 150 |
| Security Server | Medium | 250 | 250 |
| Central Server | Hard | 500 | 400 |
| Main System | Hard | 900 | 600 |

The report shows completed tasks, task runs, success rate, and the highest XP reward earned. Success rate is completed tasks divided by task runs. Starting an available puzzle counts as one run; individual answers do not count as separate runs.

## Project Files

```text
terminal-hacker/
├── main.cpp
├── Player.h
├── Player.cpp
├── Server.h
├── Server.cpp
├── Input.h
├── Input.cpp
├── Task.h
├── Task.cpp
├── Game.h
├── Game.cpp
└── README.md
```

| Files | Purpose |
| --- | --- |
| main.cpp | Starts the game |
| Player.h / Player.cpp | Player data and methods |
| Server.h / Server.cpp | Server access and progress |
| Input.h / Input.cpp | Input checks |
| Task.h / Task.cpp | Abstract task class and puzzle classes |
| Game.h / Game.cpp | Menu, map, connections, report, and game loop |

## C++ Topics Used

- Variables, operators, conditions, and loops
- Functions, function overloading, and default arguments
- Fixed one-dimensional and two-dimensional arrays
- Classes, objects, constructors, and encapsulation
- References and pointers
- Inheritance, abstraction, and polymorphism
- Virtual methods and a virtual destructor
- Static fields, const methods, this, and a friend function

The project does not use vector, map, file storage, databases, network connections, a GUI, lambdas, or STL algorithms.

## Tests

The following manual tests passed:

- Build and run
- Wrong menu input
- Actions without a server connection
- Map boundary checks
- Locked server access
- Five-guess limit
- Completed task reward checks
- Energy reaching 0
- Risk reaching 100%
- Full win: 10 completed tasks and 1500 XP
