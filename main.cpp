#include "board.h"
#include "chesspiece.h"
#include <iostream>

int main() {
    Chesspiece ch;
    Board board;
    
    board.defaultPosition();
    board.print();
    board.gameProcess();

    return 0;
};
