# Chess

Two player Chess written in C++ with CLI and GUI

![image](https://github.com/KDesp73/Chess/assets/63654361/94eb8637-c78f-4b82-81f8-93fcb1218316)

![image](https://github.com/KDesp73/Chess/assets/63654361/9cd93404-066b-4218-92b2-d377c0c6b5d0)


## Implementations

- Checkmate
- Stalemate
- King and Queen side castling
- En Passant
- Check
- Pins
- Pseudo-valid move checks
- Import - Export FEN position strings
- 3-fold repetition draw
- Draw due to insufficient material
- 50 move rule
- Pawn promotions
- Material advantage
- Export PGN of game
- GUI

## Limitations

- No computer opponent

## Basic API

### Create a board

```cpp
Board *board = new Board(std::string fen, std::string playingAs = Piece::WHITE, bool showMaterial = true, bool showMoves = true, std::string prompt_type = Board::SEPERATE);
```

### Make a move

```cpp
Board::movePiece(Move move, Board *board);
```

### Export FEN

```cpp
Board::exportFEN(Board *board);
```

### Export PGN

```cpp
board->exportPGN();
```

### Start CLI Game

```cpp
Game::start(string starting_fen, string playingAs, bool showMaterial, bool showMoves, std::string prompt_type);
```

### Start GUI Game

```cpp
GUI::init(int size, Board *board);
```

## ToDo

- [ ] PGN Import
- [ ] Computer opponent (Evaluation based and ML model)
- [x] GUI
- [x] Check if position is valid
- [x] Better FEN strings (include movefor, castling rights, enpassant etc)

## Author

[@KDesp73](http://github.com/KDesp73)

## License

[MIT](https://github.com/KDesp73/Chess/blob/main/LICENSE)
