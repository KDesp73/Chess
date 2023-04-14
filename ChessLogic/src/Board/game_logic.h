#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../Pieces/piece_declarations.h"

//game_logic.cpp
void start(string starting_fen);

string* prompt(Pieces* p, char board[][8]);

bool makeGivenMove(string *move, Pieces *p, char board[][8]);

bool turn(Pieces *p, char board[][8]);

bool isMate(char board[][8]);
bool isDraw(char board[][8]);

void gameLoop(Pieces *wp, Pieces *bp, char board[][8]);