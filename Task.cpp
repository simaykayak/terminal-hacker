#include "Task.h"
#include "Input.h"

#include <iostream>

using namespace std;

// Shared counters
int Task::completed = 0;
int Task::runs = 0;

// ==================== BASE TASK ====================

Task::Task(Server* servers, int& activeServer)
    : servers(servers), activeServer(activeServer) {
}

Task::~Task() {
}

void Task::start() {
    runs++;
}

void Task::finish() {
    completed++;
}

int Task::getCompleted() {
    return completed;
}

int Task::getRuns() {
    return runs;
}

bool Task::canStart(const Player& player) const {
    if (!player.isActive()) {
        cout << "The mission is over.\n";
        return false;
    }

    if (activeServer < 0 || activeServer >= 5) {
        cout << "Connect to a server first.\n";
        return false;
    }

    return true;
}

// ==================== CHILD CONSTRUCTORS ====================

CodeTask::CodeTask(Server* servers, int& activeServer)
    : Task(servers, activeServer) {
}

FirewallTask::FirewallTask(Server* servers, int& activeServer)
    : Task(servers, activeServer) {
}

// ==================== CODE CHECKS ====================

// First version: check the full code.
bool checkCode(const string& guess, const string& code) {
    return guess == code;
}

// Second version: count matching digits.
void checkCode(
    const string& guess,
    const string& code,
    int& right,
    int& wrong
) {
    right = 0;
    wrong = 0;

    if (guess.size() != 4 || code.size() != 4) {
        return;
    }

    bool usedCode[4] = {false, false, false, false};
    bool usedGuess[4] = {false, false, false, false};

    // Count digits in the right place.
    for (int i = 0; i < 4; i++) {
        if (guess[i] == code[i]) {
            right++;
            usedCode[i] = true;
            usedGuess[i] = true;
        }
    }

    // Count matching digits in the wrong place.
    for (int i = 0; i < 4; i++) {
        if (!usedGuess[i]) {
            for (int j = 0; j < 4; j++) {
                if (!usedCode[j] && guess[i] == code[j]) {
                    wrong++;
                    usedCode[j] = true;
                    break;
                }
            }
        }
    }
}

// ==================== CODE TASK ====================

void CodeTask::run(Player& player) {
    if (!canStart(player)) {
        return;
    }

    Server& server = servers[activeServer];

    if (server.isCodeDone()) {
        cout << "Code already solved.\n";
        return;
    }

    const string codes[5] = {
        "1324",
        "2413",
        "3142",
        "4231",
        "4321"
    };

    start();

    int tries = 5;

    cout << "\n======= CODE PUZZLE =======\n";
    cout << "Guess the four-digit code.\n";
    cout << "Use 1, 2, 3, and 4 once each.\n";

    while (tries > 0 && player.isActive()) {
        cout << "\nTries left: " << tries << "\n";
        cout << "Guess: ";

        string guess;

        if (!readText(guess)) {
            return;
        }

        bool valid = guess.size() == 4;

        if (valid) {
            for (int i = 0; i < 4; i++) {
                if (guess[i] < '0' || guess[i] > '9') {
                    valid = false;
                }
            }
        }

        if (!valid) {
            cout << "Enter exactly four digits. No try lost.\n";
            continue;
        }

        tries--;

        if (checkCode(guess, codes[activeServer])) {
            server.finishCode(player);
            finish();
            player.showStatus();
            return;
        }

        int right;
        int wrong;

        checkCode(guess, codes[activeServer], right, wrong);

        cout << "Right place: " << right << "\n";
        cout << "Wrong place: " << wrong << "\n";

        player.loseEnergy();
        player.addRisk(5);

        cout << "Lost 10 energy. Risk +5%.\n";
        player.showStatus();
    }

    cout << "\nCode task failed.\n";

    if (player.isActive()) {
        cout << "Choose 3 to start a new run.\n";
    }
}

// ==================== FIREWALL TASK ====================

void FirewallTask::run(Player& player) {
    if (!canStart(player)) {
        return;
    }

    Server& server = servers[activeServer];

    if (!server.isCodeDone()) {
        cout << "Solve this server's code first.\n";
        return;
    }

    if (server.isFirewallDone()) {
        cout << "Firewall already passed.\n";
        return;
    }

    start();

    int level = 1;

    cout << "\n======= FIREWALL PUZZLE =======\n";
    cout << "Pass all three levels.\n";

    while (level <= 3 && player.isActive()) {
        bool correct = false;
        int answer;

        cout << "\n--- Level " << level << " ---\n";

        switch (level) {
            case 1: {
                int number = 7 + activeServer;

                cout << "Number: " << number << "\n";
                cout << "Enter 0 for even or 1 for odd: ";

                if (!readNumber(answer)) {
                    return;
                }

                correct = answer == number % 2;
                break;
            }

            case 2: {
                int numbers[4] = {
                    2,
                    4,
                    5,
                    7 + activeServer
                };

                int sum = 0;

                cout << "Find the sum: ";

                for (int i = 0; i < 4; i++) {
                    sum += numbers[i];
                    cout << numbers[i] << " ";
                }

                cout << "\nAnswer: ";

                if (!readNumber(answer)) {
                    return;
                }

                correct = answer == sum;
                break;
            }

            case 3: {
                const int table[3][3] = {
                    {4, 9, 2},
                    {3, 5, 7},
                    {8, 1, 6}
                };

                int row = activeServer % 3;
                int col = (activeServer + 1) % 3;

                cout << "Find " << table[row][col] << ":\n";

                for (int r = 0; r < 3; r++) {
                    for (int c = 0; c < 3; c++) {
                        cout << table[r][c] << " ";
                    }

                    cout << "\n";
                }

                int rowAnswer;
                int colAnswer;

                cout << "Use numbers 1 to 3.\n";
                cout << "Row: ";

                if (!readNumber(rowAnswer)) {
                    return;
                }

                cout << "Column: ";

                if (!readNumber(colAnswer)) {
                    return;
                }

                correct =
                    rowAnswer == row + 1 &&
                    colAnswer == col + 1;

                break;
            }
        }

        if (correct) {
            cout << "Correct! Level passed.\n";
            level++;
        } else {
            player.loseEnergy();
            player.addRisk(10);

            cout << "Wrong answer.\n";
            cout << "Lost 10 energy. Risk +10%.\n";
            cout << "Try this level again.\n";

            player.showStatus();
        }
    }

    if (player.isActive()) {
        server.finishFirewall();
        finish();

        cout << "\nFIREWALL PASSED!\n";
        cout << "This server is complete.\n";
    } else {
        cout << "\nFirewall task failed.\n";
    }
}