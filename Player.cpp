#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string name)
    : energy(100), xp(0), level(1), risk(0) {
    this->name = name;
}

void Player::loseEnergy(int amount) {
    if (amount > 0) {
        if (amount >= energy) {
            energy = 0;
        } else {
            energy -= amount;
        }
    }
}

void Player::addXP(int amount) {
    if (amount > 0) {
        xp += amount;
        level = 1 + xp / 100;
    }
}

void Player::addRisk(int amount) {
    if (amount > 0) {
        if (amount >= 100 - risk) {
            risk = 100;
        } else {
            risk += amount;
        }
    }
}

int Player::getXP() const {
    return xp;
}

bool Player::isActive() const {
    return energy > 0 && risk < 100;
}

void Player::showStatus() const {
    cout << "\n======= PLAYER STATUS =======\n";
    cout << "Name: " << name << "\n";
    cout << "Energy: " << energy << "\n";
    cout << "XP: " << xp << "\n";
    cout << "Level: " << level << "\n";
    cout << "Risk: " << risk << "%\n";
}