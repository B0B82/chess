#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <fstream>
#include "chesspiece.h"

class ErrorFileException {};

class Board : public Chesspiece  {
    protected:
        bool boardState[64];
        bool bufferState;
        bool flag;
        bool bufferIsWhite;
        bool isWhite[64];
        std::string boardView[64];
        std::string bufferView;
        int bufferX;
        int bufferY;
        int moveCounter;
        int getX();
        int getY();
        void refresh();
    public:
        Board();
        ~Board();

        void gameProcess();
        void print();
        void defaultPosition();
        void setBoardCell(int position, std::string view = "  ", 
                            bool state = false, bool isWhite = false);
        void moveChesspiece(int x, int y);
        std::string getBoardViev(int position) const;
        bool getIsWhite(int position);
        bool getBoardState(int position) const;
        int getMoveCounter() const;
        void save();
        void load();
        friend class Test;
 };

#endif //BOARD
