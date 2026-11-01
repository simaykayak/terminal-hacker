#ifndef SERVER_H
#define SERVER_H

#include <string>
#include "Player.h"

class Server {
private:
    int id;
    std::string name;
    std::string difficulty;

    int neededXP;
    int rewardXP;

    bool locked;
    bool codeDone;
    bool firewallDone;

public:
    Server();

    Server(
        int id,
        std::string name,
        std::string difficulty,
        int neededXP,
        int rewardXP
    );

    bool connect(const Player& player);
    void showInfo() const;

    std::string getName() const;
    int getReward() const;

    bool isCodeDone() const;
    bool isFirewallDone() const;
    bool isDone() const;

    void finishCode(Player& player);
    void finishFirewall();
};

#endif