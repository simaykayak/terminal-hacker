#include "Game.h"
#include "Task.h"
#include "Input.h"

#include <iostream>

using namespace std;

// ==================== MENU ====================

void showMenu() {
    cout << "\n======= TASK CENTER =======\n";
    cout << "1. Show Network Map\n";
    cout << "2. Connect to Server\n";
    cout << "3. Solve Code\n";
    cout << "4. Pass Firewall\n";
    cout << "5. Show Player Status\n";
    cout << "6. Show Game Report\n";
    cout << "0. Exit Game\n";
    cout << "Enter a command: ";
}

// ==================== MAP ====================

void printMap(const int map[][5], int row, int col) {
    cout << "\n======= NETWORK MAP =======\n";

    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (r == row && c == col) {
                cout << "3 ";
            } else {
                cout << map[r][c] << " ";
            }
        }

        cout << "\n";
    }

    cout << "\n0 = Empty\n";
    cout << "1 = Server\n";
    cout << "2 = Security Point\n";
    cout << "3 = Player\n";
}

void showMap(const int map[][5], int& row, int& col) {
    while (true) {
        printMap(map, row, col);

        if (map[row][col] == 1) {
            cout << "\nServer found!\n";
            cout << "Press Q, then choose 2 to connect.\n";
        }

        if (map[row][col] == 2) {
            cout << "\nSecurity point found. Stay alert.\n";
        }

        cout << "\nW = Up, S = Down, A = Left, D = Right\n";
        cout << "Q = Return to menu\n";
        cout << "Move: ";

        string move;

        if (!readText(move)) {
            return;
        }

        if (move.size() != 1) {
            cout << "Enter one move.\n";
            continue;
        }

        int nextRow = row;
        int nextCol = col;

        switch (move[0]) {
            case 'w':
            case 'W':
                nextRow--;
                break;

            case 's':
            case 'S':
                nextRow++;
                break;

            case 'a':
            case 'A':
                nextCol--;
                break;

            case 'd':
            case 'D':
                nextCol++;
                break;

            case 'q':
            case 'Q':
                return;

            default:
                cout << "Invalid move.\n";
                continue;
        }

        if (nextRow < 0 || nextRow >= 5 ||
            nextCol < 0 || nextCol >= 5) {
            cout << "You cannot leave the map.\n";
        } else {
            row = nextRow;
            col = nextCol;
        }
    }
}

// ==================== CONNECTION ====================

void connectToServer(
    Server servers[],
    const int positions[][2],
    int row,
    int col,
    const Player& player,
    int& activeServer
) {
    activeServer = -1;

    for (int i = 0; i < 5; i++) {
        if (positions[i][0] == row &&
            positions[i][1] == col) {
            if (servers[i].connect(player)) {
                activeServer = i;
            }

            return;
        }
    }

    cout << "\nThere is no server here.\n";
    cout << "Move to a server first.\n";
}

// ==================== REPORT ====================

void showReport(
    const Player& player,
    const Server servers[],
    int count
) {
    int completed = Task::getCompleted();
    int runs = Task::getRuns();

    double successRate = 0.0;

    if (runs > 0) {
        successRate = 100.0 * completed / runs;
    }

    int bestServer = -1;

    cout << "\n======= GAME REPORT =======\n";

    // The friend function can read private Player fields.
    cout << "Player: " << player.name << "\n";
    cout << "Energy: " << player.energy << "\n";
    cout << "XP: " << player.xp << "\n";
    cout << "Level: " << player.level << "\n";
    cout << "Risk: " << player.risk << "%\n";

    cout << "\nCompleted tasks: "
         << completed << " / " << count * 2 << "\n";

    cout << "Task runs: " << runs << "\n";
    cout << "Success rate: " << successRate << "%\n";

    cout << "\n======= SERVER PROGRESS =======\n";

    for (int i = 0; i < count; i++) {
        cout << servers[i].getName() << "\n";

        cout << "  Code: "
             << (servers[i].isCodeDone() ? "Done" : "Not done")
             << "\n";

        cout << "  Firewall: "
             << (servers[i].isFirewallDone() ? "Done" : "Not done")
             << "\n";

        if (servers[i].isCodeDone()) {
            if (bestServer == -1 ||
                servers[i].getReward() >
                servers[bestServer].getReward()) {
                bestServer = i;
            }
        }
    }

    if (bestServer == -1) {
        cout << "\nHighest earned reward: None yet\n";
    } else {
        cout << "\nHighest earned reward: "
             << servers[bestServer].getName()
             << " ("
             << servers[bestServer].getReward()
             << " XP)\n";
    }
}

// ==================== WIN CHECK ====================

bool hasWon(const Server servers[]) {
    for (int i = 0; i < 5; i++) {
        if (!servers[i].isDone()) {
            return false;
        }
    }

    return true;
}

// ==================== GAME LOOP ====================

void runGame() {
    Player player("GHOST_01");

    Server servers[5] = {
        Server(1, "Training Server", "Easy", 0, 100),
        Server(2, "Data Server", "Easy", 100, 150),
        Server(3, "Security Server", "Medium", 250, 250),
        Server(4, "Central Server", "Hard", 500, 400),
        Server(5, "Main System", "Hard", 900, 600)
    };

    const int networkMap[5][5] = {
        {0, 1, 0, 0, 0},
        {0, 2, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {1, 0, 2, 0, 0},
        {0, 0, 0, 0, 1}
    };

    const int serverPositions[5][2] = {
        {0, 1},
        {1, 3},
        {2, 2},
        {3, 0},
        {4, 4}
    };

    int row = 0;
    int col = 0;
    int activeServer = -1;
    int choice = -1;

    CodeTask codeTask(servers, activeServer);
    FirewallTask firewallTask(servers, activeServer);

    // Base class pointers show polymorphism.
    Task* tasks[2] = {
        &codeTask,
        &firewallTask
    };

    cout << "TERMINAL HACKER v1.0\n";
    cout << "Simulation\n";
    cout << "SYSTEM ONLINE\n";

    do {
        showMenu();

        if (!readNumber(choice)) {
            break;
        }

        if (choice < 0 || choice > 6) {
            cout << "Invalid command. Choose 0 to 6.\n";
            continue;
        }

        switch (choice) {
            case 1:
                // Opening the map ends the old connection.
                activeServer = -1;
                showMap(networkMap, row, col);
                break;

            case 2:
                connectToServer(
                    servers,
                    serverPositions,
                    row,
                    col,
                    player,
                    activeServer
                );
                break;

            case 3:
                tasks[0]->run(player);
                break;

            case 4:
                tasks[1]->run(player);
                break;

            case 5:
                player.showStatus();
                break;

            case 6:
                showReport(player, servers, 5);
                break;

            case 0:
                cout << "\nGame closed. Goodbye!\n";
                break;
        }

        // Stop if the input stream ends.
        if (!cin) {
            break;
        }

        if (player.isActive() && hasWon(servers)) {
            cout << "\nMISSION COMPLETE!\n";
            cout << "You finished all five servers!\n";

            showReport(player, servers, 5);
            break;
        }

    } while (choice != 0 && player.isActive());

    if (!player.isActive()) {
        cout << "\nGAME OVER\n";
        cout << "Energy is 0 or risk is 100%.\n";

        showReport(player, servers, 5);
    }
}