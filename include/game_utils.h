#pragma once

#include "Pieces.h"
#include "board.h"
#include "board_utils.h"


#include <string>

using namespace std;

namespace GameUtils {
	Move prompt(Pieces* p, Board *board, string type);
	Move turn(Pieces *p, Board *board);
	bool isMate(Board *board);
	bool isDraw(Board *board);
	void gameLoop(Board *board);
};
