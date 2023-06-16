#pragma once

#include <string>
#include <vector>

using namespace std;

namespace AnsiTextLib{
    void menu(string title, int bgColor, std::vector<std::string> options, void (*handleOptionsFunc)(int selectedOption));
};
