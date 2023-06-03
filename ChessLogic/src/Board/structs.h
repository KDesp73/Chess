#pragma once

#include <string>

using namespace std;

struct Move{
    std::string from;
    std::string to;
};

struct Coords{
    int x;
    int y;
};

struct Square{
    string name;
    char file = name.at(0);
    int rank = stoi(to_string(name.at(1)));
    int x = rank -1;
    int y = file - 97;
};