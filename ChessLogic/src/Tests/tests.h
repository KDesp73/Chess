#pragma once

#include <vector>
#include <string>

using namespace std;

namespace Test{
    bool testCheckMate(vector<string> mate_fens);
    bool testPins(vector<string> pin_fens, vector<string> pinned_pieces);
    bool testCheck(vector<string> check_fens);
    bool testNotCheck(vector<string> should_not_be_check_fens);
} // namespace Test
