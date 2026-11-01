#ifndef TASK_H
#define TASK_H

#include "Server.h"

class Task {
private:
    static int completed;
    static int runs;

protected:
    Server* servers;
    int& activeServer;

    void start();
    void finish();

    bool canStart(const Player& player) const;

public:
    Task(Server* servers, int& activeServer);

    virtual void run(Player& player) = 0;
    virtual ~Task();

    static int getCompleted();
    static int getRuns();
};

class CodeTask : public Task {
public:
    CodeTask(Server* servers, int& activeServer);

    void run(Player& player) override;
};

class FirewallTask : public Task {
public:
    FirewallTask(Server* servers, int& activeServer);

    void run(Player& player) override;
};

// Function overloading
bool checkCode(
    const std::string& guess,
    const std::string& code
);

void checkCode(
    const std::string& guess,
    const std::string& code,
    int& right,
    int& wrong
);

#endif