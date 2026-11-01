#include "Server.h"
#include <iostream>

using namespace std;

Server::Server()
    : Server(0, "Unknown", "Easy", 0, 0) {
}

Server::Server(
    int id,
    string name,
    string difficulty,
    int neededXP,
    int rewardXP
)
    : id(id),
      name(name),
      difficulty(difficulty),
      neededXP(neededXP),
      rewardXP(rewardXP),
      locked(true),
      codeDone(false),
      firewallDone(false) {
}

bool Server::connect(const Player& player) {
    locked = player.getXP() < neededXP;

    showInfo();

    if (locked) {
        cout << "Access denied. You need more XP.\n";
        return false;
    }

    cout << "Connected to " << name << "!\n";
    return true;
}

void Server::showInfo() const {
    cout << "\n======= SERVER INFO =======\n";
    cout << "ID: " << id << "\n";
    cout << "Name: " << name << "\n";
    cout << "Difficulty: " << difficulty << "\n";
    cout << "XP needed: " << neededXP << "\n";
    cout << "XP reward: " << rewardXP << "\n";
    cout << "State: " << (locked ? "Locked" : "Open") << "\n";
}

string Server::getName() const {
    return name;
}

int Server::getReward() const {
    return rewardXP;
}

bool Server::isCodeDone() const {
    return codeDone;
}

bool Server::isFirewallDone() const {
    return firewallDone;
}

bool Server::isDone() const {
    return codeDone && firewallDone;
}

void Server::finishCode(Player& player) {
    if (!codeDone) {
        codeDone = true;
        player.addXP(rewardXP);

        cout << "\nCODE SOLVED!\n";
        cout << "+" << rewardXP << " XP\n";
    }
}

void Server::finishFirewall() {
    firewallDone = true;
}