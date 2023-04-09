#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../Pieces/piece_declarations.h"

//game_logic.cpp
void start(string starting_fen);

string* prompt(Pieces* p, char board[][8]);

void makeGivenMove(string from, string to, Pieces *p, char board[][8]);