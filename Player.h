#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player;
class Server;

void showReport(
    const Player& player,
    const Server servers[],
    int count
);

class Player {
private:
    std::string name;
    int energy;
    int xp;
    int level;
    int risk;

    friend void showReport(
        const Player& player,
        const Server servers[],
        int count
    );

public:
    explicit Player(std::string name);

    void loseEnergy(int amount = 10);
    void addXP(int amount);
    void addRisk(int amount);

    int getXP() const;
    bool isActive() const;

    void showStatus() const;
};

#endif